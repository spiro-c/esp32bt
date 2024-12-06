# esp32bt

```mermaid
graph LR
A{Esp32Bt} == "GND <-> GND" ==> B{WLED}
A{Esp32Bt} == "GPIO14 < - > GPIO14 (BLCK)" ==> B{WLED}
A{Esp32Bt} == "GPIO15 < - > GPIO15 (WS)" ==> B{WLED}
A{Esp32Bt} == "GPIO22 < - > GPIO32 (Data)" ==> B{WLED} 