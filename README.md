# WiFiDriveStation Kütüphanesi

`WiFiDriveStation` kütüphanesi, ESP32 tabanlı projelerde WiFi üzerinden robot kontrolü sağlamak amacıyla geliştirilmiştir. Bu kütüphane, bir web sunucusu aracılığıyla robotun **Teleoperasyon (Teleop)**, **Otonom** ve **Disable** modlarını kontrol etmeyi mümkün kılar. Kullanıcılar, web tarayıcısı üzerinden robotun çalışma modlarını değiştirebilir ve ilgili fonksiyonları tetikleyebilir.

## Özellikler
- **Web tabanlı kontrol**: WiFi üzerinden bir web sunucusu çalıştırarak robotu kontrol edin.
- **Mod değişimi**: Teleop, Otonom ve Disable modları arasında geçiş yapın.
- **Fonksiyonlar**: Her mod için ayrı başlatma (`init`) ve periyodik (`periodic`) işlevlerini tanımlayın.
- **Basit yapı**: Kullanıcı dostu API ile robotunuzu kolayca kontrol edin.

## Gereksinimler
- **ESP32**: Bu kütüphane yalnızca ESP32 tabanlı kartlarla uyumludur.
- **WiFi Bağlantısı**: WiFi ağına bağlanma ve WiFi AP modu gereklidir.
- **Arduino IDE**: Bu kütüphaneyi kullanabilmek için Arduino IDE'yi kurmanız gerekir.

## Kurulum

### Arduino IDE'yi kullanarak kurulum

1. **Arduino IDE**'yi açın ve **ESP32** kart desteğini ekleyin:
   - Arduino IDE'de, `Dosya` > `Tercihler` menüsüne gidin.
   - "Ekstra Kart Yöneticisi URL'leri" kısmına şu URL'yi ekleyin:
     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```

2. **ESP32 kartını seçin**:
   - `Araçlar` > `Kart` > `ESP32 Dev Module` seçeneğini seçin.

3. **WiFiDriveStation Kütüphanesini yükleyin**:
   - GitHub reposundan `WiFiDriveStation` kütüphanesini indirin veya ZIP dosyası olarak ekleyin.
   - Arduino IDE'de `Sketch` > `Include Library` > `Add .ZIP Library...` seçeneğiyle kütüphaneyi ekleyin.

## Kullanım

### Örnek Kod:

```cpp
#include <WiFiDriveStation.h>

const char* ssid = "WiFi_Ağ_Adı";        // WiFi ağ adı
const char* password = "WiFi_Şifresi";    // WiFi şifresi

WiFiDriveStation driveStation(ssid, password);

void setup() {
  Serial.begin(115200);
  driveStation.begin();
  
  // Teleop modunda kullanılacak init ve periodic fonksiyonlarını ayarlayın
  driveStation.setTeleopInitMethod(teleopInit);
  driveStation.setTeleopPeriodicMethod(teleopPeriodic);
  
  // Otonom modunda kullanılacak init ve periodic fonksiyonlarını ayarlayın
  driveStation.setAutonomInitMethod(autonomInit);
  driveStation.setAutonomPeriodicMethod(autonomPeriodic);
  
  // Disable modunda kullanılacak init ve periodic fonksiyonlarını ayarlayın
  driveStation.setDisableInitMethod(disableInit);
  driveStation.setDisablePeriodicMethod(disablePeriodic);
}

void loop() {
  // Web üzerinden gelen istemcileri kontrol et
  driveStation.update();
}

// Teleop başlangıç fonksiyonu
void teleopInit() {
  // Teleop modunda yapılacak başlangıç işlemleri
}

// Teleop periyodik fonksiyonu
void teleopPeriodic() {
  // Teleop modunda sürekli yapılacak işlemler
}

// Otonom başlangıç fonksiyonu
void autonomInit() {
  // Otonom modunda yapılacak başlangıç işlemleri
}

// Otonom periyodik fonksiyonu
void autonomPeriodic() {
  // Otonom modunda sürekli yapılacak işlemler
}

// Disable başlangıç fonksiyonu
void disableInit() {
  // Disable modunda yapılacak başlangıç işlemleri
}

// Disable periyodik fonksiyonu
void disablePeriodic() {
  // Disable modunda sürekli yapılacak işlemler
}
```
## Fonksiyonlar
- **WiFiDriveStation::begin():** Web sunucusunu başlatır ve ESP32'yi WiFi ağına bağlar.

- **WiFiDriveStation::update():** Web istemcilerinden gelen istekleri işler ve robotun mevcut moduna göre uygun işlevleri çağırır.

- **WiFiDriveStation::setTeleopInitMethod(void teleopInit):** Teleoperasyon (Teleop) modunda çalışacak başlangıç fonksiyonunu ayarlayabilirsiniz.

- **WiFiDriveStation::setTeleopPeriodicMethod(void teleopPeriodic):** Teleoperasyon (Teleop) modunda sürekli çalışacak fonksiyonu ayarlayabilirsiniz.

- **WiFiDriveStation::setAutonomInitMethod(void autonomInit):** Otonom modunda çalışacak başlangıç fonksiyonunu ayarlayabilirsiniz.

- **WiFiDriveStation::setAutonomPeriodicMethod(void autonomPeriodic):** Otonom modunda sürekli çalışacak fonksiyonu ayarlayabilirsiniz.

- **WiFiDriveStation::setDisableInitMethod(void disableInit)):** Disable modunda çalışacak başlangıç fonksiyonunu ayarlayabilirsiniz.

- **WiFiDriveStation::setDisablePeriodicMethod(void disablePeriodic):** Disable modunda sürekli çalışacak fonksiyonu ayarlayabilirsiniz.

## Web Arayüzü
WiFiDriveStation kütüphanesi bir web sunucusu çalıştırarak aşağıdaki butonlarla robotun modunu kontrol etmenizi sağlar:

- **Teleop:** Robotu manuel kontrol etme.
- **Autonom:** Robotu otonom moda geçirme.
- **Disable:** Robotu devre dışı bırakma.

Her bir buton, ilgili moda geçiş yapmak için web tarayıcısında tıklanabilir.


## Lisans
Bu proje MIT Lisansı ile lisanslanmıştır - detaylar için **LICENSE** dosyasına bakabilirsiniz.

