#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);

const char* ssid = "SSID";
const char* password =  "Password";

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void setup() {
  u8g2.begin();
  Serial.begin(115200);
  delay(4000);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

}

void loop() {

  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;

    http.begin("https://services1.arcgis.com/0MSEUqKaxRlEPj5g/arcgis/rest/services/ncov_cases/FeatureServer/1/query?where=OBJECTID%3E0&objectIds=145%2C158&time=&geometry=&geometryType=esriGeometryEnvelope&inSR=&spatialRel=esriSpatialRelIntersects&resultType=none&distance=0.0&units=esriSRUnit_Meter&returnGeodetic=false&outFields=country_region%2Cconfirmed%2Cactive%2Cdeaths&returnGeometry=false&featureEncoding=esriDefault&multipatchOption=xyFootprint&maxAllowableOffset=&geometryPrecision=&outSR=&datumTransformation=&applyVCSProjection=false&returnIdsOnly=false&returnUniqueIdsOnly=false&returnCountOnly=false&returnExtentOnly=false&returnQueryGeometry=false&returnDistinctValues=false&cacheHint=false&orderByFields=&groupByFieldsForStatistics=&outStatistics=&having=&resultOffset=&resultRecordCount=&returnZ=false&returnM=false&returnExceededLimitFeatures=true&quantizationParameters=&sqlFormat=none&f=pjson&token=");
    int httpCode = http.GET();                                        

    if (httpCode > 0) { 

      const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_ARRAY_SIZE(4) + 2*JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(4) + 3*JSON_OBJECT_SIZE(6) + 2*JSON_OBJECT_SIZE(7) + 760;
      DynamicJsonDocument doc(capacity);
      String payload = http.getString();
      
const char* json = "{\"objectIdFieldName\":\"OBJECTID\",\"uniqueIdField\":{\"name\":\"OBJECTID\",\"isSystemMaintained\":true},\"globalIdFieldName\":\"\",\"geometryType\":\"esriGeometryPoint\",\"spatialReference\":{\"wkid\":4326,\"latestWkid\":4326},\"fields\":[{\"name\":\"Country_Region\",\"type\":\"esriFieldTypeString\",\"alias\":\"Country/Region\",\"sqlType\":\"sqlTypeOther\",\"length\":8000,\"domain\":null,\"defaultValue\":null},{\"name\":\"Confirmed\",\"type\":\"esriFieldTypeInteger\",\"alias\":\"Confirmed\",\"sqlType\":\"sqlTypeOther\",\"domain\":null,\"defaultValue\":null},{\"name\":\"Active\",\"type\":\"esriFieldTypeInteger\",\"alias\":\"Active\",\"sqlType\":\"sqlTypeOther\",\"domain\":null,\"defaultValue\":null},{\"name\":\"Deaths\",\"type\":\"esriFieldTypeInteger\",\"alias\":\"Deaths\",\"sqlType\":\"sqlTypeOther\",\"domain\":null,\"defaultValue\":null}],\"features\":[{\"attributes\":{\"Country_Region\":\"Germany\",\"Confirmed\":123878,\"Active\":67229,\"Deaths\":2736}},{\"attributes\":{\"Country_Region\":\"India\",\"Confirmed\":8446,\"Active\":7189,\"Deaths\":288}}]}";
deserializeJson(doc, json);

const char* objectIdFieldName = doc["objectIdFieldName"]; // "OBJECTID"

const char* uniqueIdField_name = doc["uniqueIdField"]["name"]; // "OBJECTID"
bool uniqueIdField_isSystemMaintained = doc["uniqueIdField"]["isSystemMaintained"]; // true

const char* globalIdFieldName = doc["globalIdFieldName"]; // ""
const char* geometryType = doc["geometryType"]; // "esriGeometryPoint"

int spatialReference_wkid = doc["spatialReference"]["wkid"]; // 4326
int spatialReference_latestWkid = doc["spatialReference"]["latestWkid"]; // 4326

JsonArray fields = doc["fields"];

JsonObject fields_0 = fields[0];
const char* fields_0_name = fields_0["name"]; // "Country_Region"
const char* fields_0_type = fields_0["type"]; // "esriFieldTypeString"
const char* fields_0_alias = fields_0["alias"]; // "Country/Region"
const char* fields_0_sqlType = fields_0["sqlType"]; // "sqlTypeOther"
int fields_0_length = fields_0["length"]; // 8000

JsonObject fields_1 = fields[1];
const char* fields_1_name = fields_1["name"]; // "Confirmed"
const char* fields_1_type = fields_1["type"]; // "esriFieldTypeInteger"
const char* fields_1_alias = fields_1["alias"]; // "Confirmed"
const char* fields_1_sqlType = fields_1["sqlType"]; // "sqlTypeOther"

JsonObject fields_2 = fields[2];
const char* fields_2_name = fields_2["name"]; // "Active"
const char* fields_2_type = fields_2["type"]; // "esriFieldTypeInteger"
const char* fields_2_alias = fields_2["alias"]; // "Active"
const char* fields_2_sqlType = fields_2["sqlType"]; // "sqlTypeOther"

JsonObject fields_3 = fields[3];
const char* fields_3_name = fields_3["name"]; // "Deaths"
const char* fields_3_type = fields_3["type"]; // "esriFieldTypeInteger"
const char* fields_3_alias = fields_3["alias"]; // "Deaths"
const char* fields_3_sqlType = fields_3["sqlType"]; // "sqlTypeOther"

JsonObject features_0_attributes = doc["features"][0]["attributes"];
const char* features_0_attributes_Country_Region = features_0_attributes["Country_Region"]; // "Germany"
long features_0_attributes_Confirmed = features_0_attributes["Confirmed"]; // 114257
long features_0_attributes_Active = features_0_attributes["Active"]; // 65608
int features_0_attributes_Deaths = features_0_attributes["Deaths"]; // 2349

JsonObject features_1_attributes = doc["features"][1]["attributes"];
const char* features_1_attributes_Country_Region = features_1_attributes["Country_Region"]; // "India"
int features_1_attributes_Confirmed = features_1_attributes["Confirmed"]; // 6653
int features_1_attributes_Active = features_1_attributes["Active"]; // 5852
int features_1_attributes_Deaths = features_1_attributes["Deaths"]; // 199

Serial.println("-------------------------------");
      Serial.print("Origin: ");
      Serial.println(features_0_attributes_Country_Region);
      Serial.print("Confirmed:");
      Serial.println(features_0_attributes_Confirmed);
      Serial.print("Active:");
      Serial.println(features_0_attributes_Active);
      Serial.print("Deaths:");
      Serial.println(features_0_attributes_Deaths);
      Serial.println("-------------------------------");
      Serial.print("Origin: ");
      Serial.println(features_1_attributes_Country_Region);
      Serial.print("Confirmed:");
      Serial.println(features_1_attributes_Confirmed);
      Serial.print("Active:");
      Serial.println(features_1_attributes_Active);
      Serial.print("Deaths:");
      Serial.println(features_1_attributes_Deaths);
      Serial.println("-------------------------------");

      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0,10);
      u8g2.print(String(features_0_attributes_Country_Region));
      u8g2.setCursor(0,20);
      u8g2.print(String(features_0_attributes_Confirmed) + " Confirmed");
      u8g2.setCursor(0,30);
      u8g2.print(String(features_0_attributes_Active) + " Active");
      u8g2.setCursor(0,40);
      u8g2.print(String(features_0_attributes_Deaths) + " Deaths");
      u8g2.sendBuffer();          // transfer internal memory to the display
      delay(5000);
      u8g2.clearDisplay();
      u8g2.clearBuffer();          // clear the internal memory
      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setCursor(0,10);
      u8g2.print(String(features_1_attributes_Country_Region));
      u8g2.setCursor(0,20);
      u8g2.print(String(features_1_attributes_Confirmed) + " Confirmed");
      u8g2.setCursor(0,30);
      u8g2.print(String(features_1_attributes_Active) + " Active");
      u8g2.setCursor(0,40);
      u8g2.print(String(features_1_attributes_Deaths) + " Deaths");
      u8g2.sendBuffer();          // transfer internal memory to the display
      delay(5000);
      u8g2.clearDisplay();

    }

    else {
      Serial.println("Error on HTTP request");
    }

    http.end();
    }

  delay(100);
  
}
