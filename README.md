# NixieClock
Horloge effet tubes type 'Nixie' sur TFT 480x320

![NixieClock](https://github.com/user-attachments/assets/63c829ac-6304-44e7-9e2a-a9d5687044bb)

Horloge simulant l'utilisation de tubes type 'Nixie'.
La mise à l'heure s'effectue par accès à un serveur NTP puis choix de la Time Zone.

En suite initialisation de l'heure pour la bibliothèque Time.h, puis coupure du WiFi.

En cas de dérive de l'heure, il suffit de redémarer l'horloge.


Un grand merci kirapolyarush pour le partage de ses resources.

https://www.deviantart.com/kirapolyarush/art/Nixie-Tube-Numbers-Resource-468478031


et Bodmer pour ses librairies

https://github.com/Bodmer/TFT_eSPI https://github.com/Bodmer/TJpg_Decoder

Autres bases acquises sur le site Randomnerdtutorials

https://randomnerdtutorials.com/install-esp32-filesystem-uploader-arduino-ide/ 

https://randomnerdtutorials.com/esp32-date-time-ntp-client-server-arduino/#more-95109


