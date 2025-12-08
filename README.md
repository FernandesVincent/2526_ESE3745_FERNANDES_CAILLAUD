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

Donc le temps de commutation total pour monter est de 46 ns et pour descendre 74ns. Ce qui correspond au dead time (DT) est donc 120ns. On prend plus pour être large (200ns).
![](/Photos/temps_mort.png)

En regardant sur l'ioc, on a pour les pins de la phase U, PA8 et PB13 ce qui correspond respectivement à TIM1_CH1 et TIM1_CH1N et pour la phase V, PA9 et PB14 ce qui correnspond à TIM1_CH2 et TIM1_CH2N.

On choisit ensuite nos valeurs pour ARR et PSC afin d'avoir 20kHz. Les valeurs ARR = 8499 et PSC = 0 correspondent.  
On choisit aussi une valeure pour le pulse qui va correspondre à notre rapport cyclique ie 60%. On prend donc 0.6*ARR ce qui donne pour pulse 5099.

Pour choisir le dead time dans l'ioc, on a : DT = valeur / f_clk avec f_clk=170MHz
On obtient donc pour valeur : 34.

Ainsi on a les 4 PWM et le dead time:  
![](/photos/DT_1.jpg)
![](/Photos/DT_2.jpg) 

### 6.2 Commande de vitesse

On réalise ensuite de quoi changer le rapport cyclique et on a dans le shell:  
![](/Photos/rapportcycl.png)

On passe maintenant en mode center-aligned (up and down ie mode 3). Donc comme ARR compte de 0 à ARR-1 puis de ARR-1 à 0 c'est-à-dire que l'on a deux cycles par périodes. Pour garder la fréquence que l'on veut il faut donc augmenter l'ARR en le multipliant par deux pour diminuer la fréquence par deux et pour que le moteur continue de travailler à 20kHz.

En  allimentant le moteur et en regardant le courant et la tension, on voit qu'il ne faut pas mesurer la tension lors du changement d'état car il y a des altérations qui empèchent une lecture correcte. On remarque aussi une variantion du courant car la bobine du moteur se charge et se décharge et il y a aussi une valeure moyenne non nulle.

On remarque aussi que lorsqu'il n'y a pas de montée progressive de la PWM lorsque l'on démarre la moteur, il y a un appel de courant qui décharge les condensateurs ce qu'il faut éviter.



