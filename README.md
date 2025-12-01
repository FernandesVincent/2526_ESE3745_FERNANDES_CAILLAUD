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

Donc le temps de commutation total pour monter est de 46 ns et pour descendre 74ns. Ce qui correspond au dead time est donc le temps de descente, ie 74ns. 
![](/Photos/temps_mort.png)

En regardant sur l'ioc, on a pour les pins de la phase U, PA8 et PB13 ce qui correspond respectivement à TIM1_CH1 et TIM1_CH1N et pour la phase V, PA9 et PB14 ce qui correnspond à TIM1_CH2 et TIM1_CH2N.

On choisit ensuite nos valeurs pour ARR et PSC afin d'avoir 20kHz. Les valeurs ARR = 8499 et PSC = 0 correspondent.  
On choisit aussi une valeure pour le pulse qui va correspondre à notre rapport cyclique ie 60%. On prend donc 0.6*ARR ce qui donne pour pulse 5099.
