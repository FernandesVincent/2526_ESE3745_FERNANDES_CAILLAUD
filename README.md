# 2526_ESE3745_FERNANDES_CAILLAUD
TP Actionneur


## 6 Commande MCC basique
### 6.1 Génération de 4 PWM

On génère 4 PWM pour controller le hacheur.

cahier des charges :  
- fréquence PWM : 20kHz
- résolution minimum : 10 bits  
- temps morts minimum :  
    - turn-on delay time, t_d(on) = 11ns
    - rise time, t_r = 35ns
    - turn-off delay time, t_d(off) = 39ns
    - fall time t_f = 35ns

Donc le temps mort total pour monter est de 46 ns et pour descendre 74ns.  
![](/Photos/temps_mort.png)

  
