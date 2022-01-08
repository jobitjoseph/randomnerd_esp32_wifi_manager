// hello
// https://oshwlab.com/l.dijkman/esp32-dev-kit-38-pin-to-spi-touch-tft
// https://github.com/ldijkman/ART-ESP32-Touch-TFT-Thermostat
// http://www.Arduino.TK
//
// https://m.facebook.com/groups/2643123052617990
//
// GNU General Public License,
// which basically means that you may freely copy, change, and distribute it,
// but you may not impose any restrictions on further distribution,
// and you must make the source code available.
//

// standalone program for test 


#include <NTPClient.h>                                  // https://github.com/arduino-libraries/NTPClient
#include <WiFi.h> // for WiFi shield
#include <WiFiUdp.h>
#include <TimeLib.h>                                   // https://github.com/PaulStoffregen/Time

const char *ssid     = "Bangert-30-Andijk";
const char *password = "ikwilerin";


int last_second = 0, second_ = 0, minute_ = 0, hour_ = 0, day_ = 0, month_ = 0, year_ = 0;

const char *monthname[13] = {"null", "Januari", "Februari", "March", "April", "May", "Juni",
                             "Juli", "Augustus", "September", "October", "November", "December"
                            };
char dayname[8][12] = {"null", "Sunday ", "Monday ", "Tuesday ", "Wednesday ", "Thursday ", "Friday ", "Saturday "};



WiFiUDP ntpUDP;

// You can specify the time server pool and the offset, (in seconds)
// additionaly you can specify the update interval (in milliseconds).
NTPClient timeClient(ntpUDP, "time.google.com", 3600, 24*60*60*1000); // 3600 sec = 1 hour offset and update every 24 hours

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();

   unsigned long unix_epoch = timeClient.getEpochTime();    // Get Unix epoch time from the NTP server

  Serial.println(timeClient.getFormattedTime());
  
  Serial.println(timeClient.getDay());
  Serial.println(timeClient.getEpochTime());

  second_ = second(unix_epoch);

    minute_ = minute(unix_epoch);

    hour_   = hour(unix_epoch);

    day_    = day(unix_epoch);

    month_  = month(unix_epoch);

    year_   = year(unix_epoch);





    // Send time and date to serial monitor

    Serial.print(hour_);
    Serial.print(":");
    Serial.print(minute_);
    Serial.print(":");
    Serial.println(second_);

    Serial.print(day_);
    Serial.print(" ");
    Serial.print(month_);
    Serial.print(" ");
    Serial.println(year_);

    Serial.print("day number of the week ");
    Serial.println(weekday(unix_epoch));

    
    Serial.print(hour_);
    Serial.print(":");
    if (minute_ < 10)Serial.print("0");
    Serial.print(minute_);
    Serial.print(":");
    if (second_ < 10)Serial.print("0");
    Serial.print(second_);
    Serial.print("  ");
    
Serial.println("  ");
Serial.println("seconds today");
unsigned long secondstoday = ((hour_*60*60)+(minute_*60)+second_);
Serial.print(secondstoday);
    Serial.println("  ");

    Serial.print(day(unix_epoch));
    Serial.print(" ");
    Serial.print(month(unix_epoch));
    Serial.print(" ");
    Serial.print(year(unix_epoch));
    Serial.print("  ");

    Serial.print(dayname[weekday(unix_epoch)]);
    Serial.print(" ");
    Serial.print(day(unix_epoch));
    Serial.print(" ");

    Serial.print(monthname[month(unix_epoch)]);
    Serial.print(" ");
    Serial.print(year(unix_epoch));
    Serial.print("  ");

    last_second = second_;


  delay(1000);
}
