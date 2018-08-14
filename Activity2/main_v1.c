#include "STM32f10x.h"

/*****************************************************************
Preambule : indiquez ici les periopheriques que vous avez utilisez
*****************************************************************/

// GPIOA   : broche 6 pour controler la LED verte
// GPIOC : broche 13 pour detecter l'appui du bouton


/*****************************************************************
Declaration des fonctions²²
*****************************************************************/
int rand(void);
void configure_gpio_pa5(void) ;
void configure_gpio_pc13(void) ;
void set_gpio(GPIO_TypeDef *GPIO, int n) ;
void reset_gpio(GPIO_TypeDef *GPIO, int n) ;
void configure_timer(TIM_TypeDef *TIM, int psc, int arr) ;
void configure_it(void) ;
void start_timer(TIM_TypeDef *TIM) ;
void stop_timer(TIM_TypeDef *TIM) ;
void change_status_gpio(GPIO_TypeDef *GPIO, int n);

/*****************************************************************
Varibales globales
 *****************************************************************/

int pressed = 0;

/*****************************************************************
MAIN
*****************************************************************/

int main(void){
	
    // Configuration des ports d'entree/sortie
	configure_gpio_pa5();
	configure_gpio_pc13();
    // Ecrire la suite du code
	configure_timer(TIM2, 7199, ((rand() * 10) - 1));
	configure_it();
	start_timer(TIM2);
    
    // Boucle d'attente du processeur
	while (1);
    
	return 0;
}

/*****************************************************************
Corps des fonctions
*****************************************************************/

/**
Configure la broche 5 du port A (led verte)
*/
void configure_gpio_pa5(void){
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // Active l'horloge pour le port A
	
	GPIOA->CRL &= ~(0xF << 20); // Mise des bits de configuration du gpio 5 du port A a 0
	GPIOA->CRL |= (0x3 << 20); // Configuration des bits pour mettre le gpio 5 du port A en output push pull
}

/**
Configure la broche 13 du port C (bouton USER) 
*/
void configure_gpio_pc13(void) {
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // On active l'horloge pour les AFIOs
	
	AFIO->EXTICR[3] &= ~(0xF << 4); // on s'asssure que les AFIO 13 (port A,B,C, et D) soient desactive pour les External interrupts
	AFIO->EXTICR[3] |= (0x2 << 4); // On active seulement l'entree 13 du port C pour l'external interrupt
	
	EXTI->IMR |= (0x1 << 13); // On ne masque pas la requete d'interruption
	EXTI->EMR |= (0x1 << 13); // Ni celle d'evenement
	EXTI->FTSR |= (0x1 << 13); // On s'assure que l'interruption aura lieu sur un front descendant (appuye sur le bouton)
	EXTI->RTSR &= ~(0x1 << 13); // Et non sur un front montant (le bouton est relache)
	EXTI->SWIER &= ~(0x1 << 13); // On desactive le bit numero 13 de ce registre
}

/**
Met a 1 la broche n du port GPIO
*/
void set_gpio(GPIO_TypeDef *GPIO, int n) {
	GPIO->ODR |= (0x1 << n); // on passe le nieme bit a 1 pour activer la sortie
}

/**
Met a 0 la broche n du port GPIO
*/
void reset_gpio(GPIO_TypeDef *GPIO, int n) {
	GPIO->ODR &= ~(0x1 << n); // on passe nieme bit a 0 pour desactiver la sortie
}

/**
Change l'etat la broche n du port GPIO
*/
void change_status_gpio(GPIO_TypeDef *GPIO, int n) {
	GPIO->ODR ^= (0x1 << n); // on passe nieme bit a 0 pour desactiver la sortie
}

/**
Configure la periode du timer TIM en fonction des parametres
psc (prescaler) et arr (autoreload) sans lancer le timer
*/
void configure_timer(TIM_TypeDef *TIM, int psc, int arr) {
	RCC->APB1ENR |= (0xF << 0); // Activation des horloges pour les timers 2 a 5
	TIM->ARR = arr;   // on affecte l'autoreload passe en argument au registre du timer concerne
	TIM->PSC = psc;		// meme chose pour le prescaler
}

/**
Demarre le timer TIM
*/
void start_timer(TIM_TypeDef *TIM) {
	TIM->CR1 |= TIM_CR1_CEN; // on active le timer, en mettant le bit CEN du
}

/**
Arrete le timer TIM
*/
void stop_timer(TIM_TypeDef *TIM) {
	TIM->CR1 &= ~TIM_CR1_CEN; // On desactive le timer en mettant le bit CEN du registre CR1 a 0
}

/**
Configure toutes les interruptions du systeme
*/
void configure_it(void) {
	NVIC->ISER[1] |= (0x1 << 8); // On active les interruption externe 10 a 15 (bouton)
	NVIC->IP[40] |= (7 << 4); // on leur donne une priorite de 7
	
	NVIC->ISER[0] |= (0x1 << 28); // active les interruptions pour le timer 2
	NVIC->IP[28] |= (8 << 4);     // On met la priorite de l'interruption pour le timer 2 sur 8
	
	NVIC->ISER[0] |= (0x1 << 29); // active les interruptions pour le timer 3
	NVIC->IP[29] |= (9 << 4);			// On met la proiorite de l'interruption pour le timer 3 sur 9
}

/*****************************************************************
Fonctions d'interruption
*****************************************************************/

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF; // on clear le flag d'interruption en le mettant a 0
	
	/*	Si l'utilisateur n'a pas encore appuye sur le bouton */
	if (!pressed)
	{
		stop_timer(TIM2);        // on arrete le timer 2
		configure_timer(TIM3, 7199, 299); // on configure le timer 3 pour les 300ms
		set_gpio(GPIOA, 5); // oon allume la LED tant que le flag  du timer 3 n'est pas mis a jour
		start_timer(TIM3); // on active le timer 3
	}
	else
		change_status_gpio(GPIOA, 5); // on change l'etat de la LED a chaque interruption (sequence final)
}
	
void TIM3_IRQHandler(void)
{
	TIM3->SR &= ~TIM_SR_UIF; // on clear le flag du timer 3
	stop_timer(TIM3); // on arrete le timer
	reset_gpio(GPIOA, 5); // on etteint la LED
	if (pressed)
		configure_timer(TIM2, 7199, 2499); // Configuration du timer 2 si l'utilisateur a appuye sur le bouton 
	else
		configure_timer(TIM2, 7199, ((rand() * 10) - 1)); // sinon on recommence
	start_timer(TIM2); // on demarre le timer 2
}

void EXTI15_10_IRQHandler(void)
{
	EXTI->PR |= (0x1 << 13); //On clear le flag de l'interruption externe ligne 13 en le mettant a 1
	pressed = 1; // On affecte 1 a la variable globale pressed pour signaler un appuye sur le bouton
}
	

/*****************************************************************
Fonctions pre-definies
*****************************************************************/

/**
Retourne une valeur entiere aleatoire comprise entre 800 et 1800
*/
int rand(){
	static int randomseed = 0;
	randomseed = (randomseed * 9301 + 49297) % 233280;
	return 800 + (randomseed % 1000);
}

