# DHT11 ve I2C LCD Tabanlı Endüstriyel Dijital Termometre

Bu proje, bir mühendislik disipliniyle basitten karmaşığa doğru tasarladığım donanım serisinin ilk adımıdır. Projede ortamdaki sıcaklık ve nem verileri işlenerek kullanıcıya dinamik bir arayüz ve akıllı uyarı sistemi sunulmaktadır. Proje önce Altium Designer üzerinde şematik ve PCB olarak tasarlanmış, ardından breadboard üzerinde fiziksel olarak kurularak test edilmiştir.

## 🛠️ Tasarım Özellikleri ve Kazanımlar
- **Mikrodenetleyici Mimarisi:** ATmega328P tabanlı standalone yapı şematize ve fiziksel olarak entegre edilmiştir.
- **I2C Hat Optimizasyonu:** LCD ekranın veri (SDA) ve saat (SCL) hatları sinyal bütünlüğünü korumak adına optimize edilmiş ve sadece 2 pin üzerinden haberleşme sağlanmıştır.
- **Gürültü Filtreleme (Mühendislik Dokunuşu):** DHT11 sensörünün besleme hatlarındaki anlık dalgalanmaları önlemek amacıyla VCC-GND arasına 100nF dekuplaj kondansatörü paralel olarak şematiğe eklenmiştir.
- **Kararlı Arayüz Kontrolü:** Ekran modları arasındaki geçiş için buton hattına 10K Ohm harici Pull-Up direnci eklenerek sinyal kararsızlığı (Floating) engellenmiştir. Yazılımsal olarak da buton arklarını önleyen Debounce algoritması kurulmuştur.
- **Çift Katmanlı PCB Tasarımı:** Kart yönlendirmesi Top (Kırmızı) ve Bottom (Mavi) katmanlar kullanılarak, imalat kurallarına (DRC) tam uyumlu, sıfır hata (0 Warnings, 0 Errors) ile tamamlamıştır.

## 💻 Kullanılan Komponentler
- ATmega328P (Arduino Uno)
- DHT11 Isı ve Nem Sensörü
- I2C Modüllü 16x2 LCD Ekran
- RGB LED (Akıllı durum uyarısı için)
- Push Button (Ekran modları arası geçiş için)
- 330 Ohm Akım Sınırlama Dirençleri & 10K Ohm Pull-Up Direnci

## 🧠 Algoritma ve Hata Yakalama Mekanizması
Yazılım mimarisinde sensör kopmaları veya veri bozulmalarına karşı endüstriyel standartta `isnan` (Not a Number) kontrol mekanizması kurulmuştur. Sensör bağlantısı koptuğu anda sistem bunu otomatik olarak algılayıp LCD ekranda "Sensor Baglantisi Kontrol Ediniz!" uyarısı vermekte ve RGB LED'i kırmızı hata moduna geçirmektedir. Sıcaklık 30°C üzerine çıktığında ise sistem otomatik olarak kırmızı alarm durumuna geçmektedir.
