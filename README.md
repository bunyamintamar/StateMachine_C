# State Machine (Durum makinesi)
Bu örnekte **C** ile basit bir state machine çalışması yapılacaktır.  
Öncelikle _**"state machine (durum makinesi) nedir?"**_ sorunu cevaplayalım.  

## State machine (durum makinesi) nedir?
Farklı girişlere göre farklı durumlarda çalışılacaksa aklımıza ilk gelen yöntem if-else ya da switch yapısını kullanmaktır. Birkaç tane if-else ya da birkaç case'den oluşan switch yapılalarıyla işimizi kolayca halledebiliyorsak sıkıntı yok. Fakat, çok fazla durum ve girdi söz konusuysa kodumuzu if-else salatasına çevirebiliriz. Bir de ileride değişiklik yapmak zorunda kalırsak vay halimize.  
İşte bunun gibi durumlarla baş edebilmek için durum makinesi yöntemi kullanılmaktadır.  

_**Durum makinesi** yerine **state machine** kelimesini kullanacağım._  

State machine ile girdileri, durumları ve içinde bulunulan duruma ve girdiye göre yapılacak eylemleri bir tablo halinde tasarlayıp daha sade bir yapı oluşturabiliriz.  Daha detaylı bir anlatımı başka kaynaklarda da bulabilirsiniz.

Örneğimizde bir arabanın farklı girdi ve durumlarına göre çalışan bir state machine çalışması bulunmaktadır.  
State machine'i oldukta basit bir şekilde anlatmak istediğim için basit girdi ve durumları kullanıdm.  
Arabanın üç farklı hızına ve pedalların üç farklı girdisine göre yeni durumlara geçişleri organize eden bir state machine tasarladım.  

_**Girdi** yerine **event** kelimesini kullanacağım._

**States**  
```c
enum states
{
    ST_LOW_SPEED,
    ST_MIDDLE_SPEED,
    ST_HIGH_SPEED,
    MAX_STATES
};
```
**states** değişkenlerinde en sonda **MAX_STATES** isimli üyenin olduğuna dikkat edin. **State** ve **Event**'lerde her zaman bu şekilde bir sonlandırıcı kullanın. İleride bu üyeler kullanılacaktır.  

**Events**
```c
enum events
{
    EV_PRESS_BREAK,
    EV_NOTHING,
    EV_PRESS_GAS,
    MAX_EVENTS
};
```

Yukarıdaki **state** ve **event**'lere göre **action**'ların seçildiği bir tablo tasarlayacağız. Tabi öncelikle **action**'larımızı belirleyelim.  
**Action**'larda geçiş esnasında yapılacak işlermler ve geçilen **state** belirtilir.  
```c
void ACT_low_speed_press_break(void);
void ACT_low_speed_nothing(void);
void ACT_low_speed_press_gas(void);
void ACT_middle_speed_press_break(void);
void ACT_middle_speed_nothing(void);
void ACT_middle_speed_press_gas(void);
void ACT_high_speed_press_break(void);
void ACT_high_speed_nothing(void);
void ACT_high_speed_press_gas(void);
```

**Action**'ların içini istediğimiz gibi doldurabiliriz. Ben buradaki örnekte sadece geçiş yapılan **state**'leri belirttim. Amacım olabildiğince basit bir şekilde anlatmak.  

Şimdi geçişleri (transitions) belirten tablomuzu tasarlayalım.  
```c
void (*StateTable[MAX_STATES][MAX_EVENTS])(void) =
{
    {ACT_low_speed_press_break,     ACT_low_speed_nothing,     ACT_low_speed_press_gas},
    {ACT_middle_speed_press_break,  ACT_middle_speed_nothing,  ACT_middle_speed_press_gas},
    {ACT_high_speed_press_break,    ACT_high_speed_nothing,    ACT_high_speed_press_gas}
};
```
Yukarıdaki iki boyutlu dizide **action** fonksiyonlarının pointer'larını belirttim. Bu tabloyu başka şekilde de tasarlayabilirsiniz.  
Aşağıda bu tablonun kullanım şeklini görebilirsiniz.  
```c
(*StateTable[2][1])(void);  // ACT_high_speed_nothing() fonksiyonu çağrılıyor
```

Bu tabloda girdiler **state** ve **event** değerleridir. Çıktı ise **action** fonksiyonunun yapacağı eylemdir.  

Şimdi bu kullanım şeklini daha basit hale getirelim. Bunun için `EventHandler(enum events ev)` fonksiyonumuzu kullanacağız.  
Şimdi diyeceksiniz ki _"Bu fonksiyonun sadece bir girdisi var. **state** değerini de girmemiz gerekmiyor mu?"_  
**state** değerini tutacak bir değişken tanımlayacağız ve bu değişkeni kullanıcının bilmesine gerek yok.  
Sadece dışarıdan girilen **event** bilgisine göre **state machine** çalışacak ve belirlenen **action** uygulandıktan sonra belirlenen **state**'e gidilecek.  
```c
enum states current_state = ST_LOW_SPEED;  // İlk state bildirildi

void EventHandler(enum events ev)
{
    (*StateTable[current_state][ev])();
}
```

Burada dikkat edilmesi gereken bir husus var. O da **state machine**'e ilk **state**'i bildirmek. Daha sonra girilen **action**'lara göre yeni state değeri belirlenecek.  

Yukarıda belirtine **action**'lardan birini inceleyelim.  
```c
void ACT_low_speed_press_break(void)
{
    // İstediğin işlemi yaptır


    enum states old_state = current_state;
    current_state = ST_LOW_SPEED;

    printTransition(old_state, current_state);  // Geçişleri ekranda gör
}
```

Gördüğünüz gibi çok basit bir state machine tasarımı yaptık. Yukarıda `printTransition(...)` fonksiyonu ile geçişleri görebiliriz. Bu örnekte amacım sadece geçişleri göstermekti. Daha detaylı bir şekilde incemek için kodları indirip çalıştırmanızı tavsiye ederim.  

Ben bu çalışmayı Linux'te yaptığım için kolayca derleyip çalıştırabilmek amacıyla bir **script** yazdım. İsteyen Windows'ta başka türlü de çalıştırabilir. Linux'te yapmanız gereken tek şey dosyaların olduğu dizinde yeni bir terminal açıp şu kodu çalıştırmak:  
```shell
chmod +x build_test.sh   // Bu satırı bir kez çalıştırmanız yeterli
./build_test.sh          // Her build işleminde bu satırı çalıştırmalısınız
```

Kolay gelsin

* * *
**Bünyamin TAMAR** - https://www.linkedin.com/in/bunyamintamar