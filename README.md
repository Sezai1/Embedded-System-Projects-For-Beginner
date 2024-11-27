1. GPIO output kullanılarak mikroişlemci pinlerine bağlı built-in LED’leri aç ve kapat. 
2. GPIO input kullanarak buton okuması yap. 
3. GPIO input interrupt kullanarak buton okuması yap ve her basışta farklı bir ledi yak. 
4. ADC polling metodu kullanarak bir pinden 12 bit çözünürlükte analog değer okuması yap. Bu 
değerin 1 saniyede 10 kere örneklemesi yapılarak ortalamasını debug arayüzünde göster. 
5. Butona basıldıktan 2 saniye sonra LED yakma işlemini sistem TIMER ile yap. 
6. Butona basıldıktan sonra 1 saniye yanıp 1 saniye sönük kalan LED kontrol işlemini sistem 
TIMER ile yap. 
7. UART polling metodu kullanılarak bilgisayar ve mikroişlemci arasında haberleşme yapılmalıdır. 
Mikroişlemci her 1 saniyede bir kere ”Hello World” verisini göndermelidir. Bu aşamada USB-TTL 
dönüştürücü ve Hercules uygulaması kullanılabilir. 
8.  UART interrupt metodu kullanılarak gibi kaç tane built-in LED var ise pc üzerinden gönderilen 
“0”, “1”, “2”, …  gibi UART mesajına göre ilgili LED toggle edilmeli. 
9.  Geliştirme kartı üzerinde bulunan FLASH hafızaya adını ve soyadını kaydet. Kartın güç 
bağlantılarını çek ve içine yazdığın verileri debug ekranında okuyarak görüntüle. 
10. CRC 16 bit hesap yapan yazılımsal fonksiyonunu hazırla. Sana UART üzerinden gönderilen 10 
byte uzunluğundaki mesaj için CRC16 hesabını yap ve mesajın sonuna ekle ve UART üzerinden 
geldiği yere geri gönder. 
11. PWM sinyalini TIMER ile oluştur. Frekans 50 Hz olmalı. Sana verilen 0 değeri için minimum 
doluluk, 2000 değeri için de maximum doluluk veren fonksiyonu yaz. 
3 / 8 
www.intetra.com.tr 
intetra 
Gömülü Yazılım Çalışma Programı 
25.08.2023 
12. Bir projene Watchdog ekle. Projende butona basıldığı zaman 10 saniye boyunca HAL_Delay’de 
kalsın. Senin eklediğin watchdog 5 saniye boyunca tetik almazsa karta reset atsın. 
13. FreeRTOS kullanılarak 2 adet LED, farklı thread’ler içerisinde ilki 200ms ikincisi de 300ms 
aralıklarla yakılır ve söndürülür. 
