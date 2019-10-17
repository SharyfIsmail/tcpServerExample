/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file : main.c
 * @brief : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 * www.st.com/SLA0044
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes —----------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "lwip.h"

/* Private includes —--------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "string.h"
/* USER CODE END Includes */

/* Private typedef —---------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#include "lwip/sockets.h"
/* USER CODE END PTD */

/* Private define —----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro —-----------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables —-------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId handle1;
osThreadId handle2;
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes —---------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void StartDefaultTask(void const * argument);

/* USER CODE BEGIN PFP */
static void client_socket_thread1(void const * argument);

/* USER CODE END PFP */
static void client_socket_thread2(void const * argument);

/* Private user code —-------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	/* USER CODE BEGIN 2 */

	/* USER CODE END 2 */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of defaultTask */
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 1024);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Configure the

	 main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE()
	;
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 168;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 4;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOH_CLK_ENABLE()
	;
	__HAL_RCC_GPIOC_CLK_ENABLE()
	;
	__HAL_RCC_GPIOA_CLK_ENABLE()
	;
	__HAL_RCC_GPIOB_CLK_ENABLE()
	;

}

/* USER CODE BEGIN 4 */
typedef struct struct_client_socket_t {
  struct sockaddr_in remotehost;
  socklen_t sockaddrsize;
  int accept_sock;
} struct_client_socket;
struct_client_socket client_socket01,client_socket02;
static void client_socket_thread1(void const * argument) {

	static char data[566];
	char data1[4];
	data1[0]='f';
	data1[1]='u';
	data1[2]='c';
	data1[3]='k';
	int a;
	//int  accept_sock;
	//struct sockaddr_in remotehost;
	//socklen_t sockaddrsize;
	//struct_client_socket *arg_client_socket;
	//arg_client_socket = (struct_client_socket*) argument;
	//remotehost = arg_client_socket->remotehost;
	//sockaddrsize  = arg_client_socket->sockaddrsize;
	//accept_sock = arg_client_socket->accept_sock;
	while (1)
	{
		a=recv( client_socket01.accept_sock,data, sizeof(data), 0);
		//while( (recv( accept_sock,data, sizeof(data), 0))==ERR_OK)
		//{
			sendto(client_socket01.accept_sock,data1,sizeof(data1),0,(struct sockaddr *)&client_socket01.remotehost, client_socket01.sockaddrsize);
		//}
			if(a==0)
			{

		 close(client_socket01.accept_sock);
		 memset(&client_socket01, 0 , sizeof(client_socket01));
		 osThreadTerminate(handle1);
			osThreadYield();
			}
	}
}

static void client_socket_thread2(void const * argument) {

static 	char data[566];


	char data1[4];
	data1[0]='f';
	data1[1]='u';
	data1[2]='c';
	data1[3]='k';
	int a;




//	int  accept_sock;
//	struct sockaddr_in remotehost;
//	socklen_t sockaddrsize;
//	struct_client_socket *arg_client_socket;
//	arg_client_socket = (struct_client_socket*) argument;
//	remotehost = arg_client_socket->remotehost;
//	sockaddrsize  = arg_client_socket->sockaddrsize;
//	accept_sock = arg_client_socket->accept_sock;
	while (1)
	{
		a=recv( client_socket02.accept_sock,data, sizeof(data), 0);
		//while( (recv( accept_sock,data, sizeof(data), 0))==ERR_OK)
		//{
			sendto(client_socket02.accept_sock,data1,sizeof(data1),0,(struct sockaddr *)&client_socket02.remotehost, client_socket02.sockaddrsize);
		//}
			if(a==0)
			{
		 close(client_socket02.accept_sock);
			memset(&client_socket02, 0 , sizeof(client_socket02));

		 osThreadTerminate(handle2);
			osThreadYield();
			}
	}
}
/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief Function implementing the

 defaultTask thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument) {

	/* init code for LWIP */
	MX_LWIP_Init();

	/* USER CODE BEGIN 5 */
	int sock, accept_sock;
	 socklen_t sockaddrsize;
	  struct sockaddr_in address, remotehost;
	 if ((sock = socket(AF_INET,SOCK_STREAM, 0)) >= 0)
	   {
	     address.sin_family = AF_INET;
	     address.sin_addr.s_addr = INADDR_ANY;
	     address.sin_port = htons(80);
	     if (bind(sock, (struct sockaddr *)&address, sizeof (address)) ==  0)
	     {
	     	listen(sock, 2);
	       for(;;)
	       {



	         accept_sock = accept(sock, (struct sockaddr *)&remotehost, (socklen_t *)&sockaddrsize);

	/* Infinite loop */
	         if(accept_sock == 1 )
	         {
	        	 client_socket01.accept_sock = accept_sock;
	        	 client_socket01.remotehost = remotehost;
	        	 client_socket01.sockaddrsize = sockaddrsize;
	        	 handle1 = sys_thread_new("client_socket_thread", (lwip_thread_fn)client_socket_thread1, (void*)&client_socket01, DEFAULT_THREAD_STACKSIZE, osPriorityNormal );
	        	// if (client_socket02.accept_sock ==2 )
	        	if (client_socket02.accept_sock == 2)
	        	 {
	        		 close(client_socket02.accept_sock);
		        		memset(&client_socket02, 0 , sizeof(client_socket02));

	        		 osThreadTerminate(handle2);
	        	 }
	         }

	         if(accept_sock == 2 )
	         {
	        	 client_socket02.accept_sock = accept_sock;
	        	 client_socket02.remotehost = remotehost;
	        	 client_socket02.sockaddrsize = sockaddrsize;
	        	 handle2 = 	 sys_thread_new("client_socket_thread", (lwip_thread_fn)client_socket_thread2, (void*)&client_socket02, DEFAULT_THREAD_STACKSIZE, osPriorityNormal );
	        	// if (client_socket01.accept_sock ==1 )
	        	 if (client_socket01.accept_sock == 1)
	        	 {
	        		 close(client_socket01.accept_sock);
	     			memset(&client_socket01, 0 , sizeof(client_socket01));

	        		 osThreadTerminate(handle1);
	        	 }
	         }
	       }
	            }
	            else
	            {
	              close(sock);
	              return;
	            }
	          }
	/* USER CODE END 5 */
}

/**
 * @brief Period elapsed callback in non blocking mode
 * @note This function is called when TIM1 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM1) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

/**
 * @brief This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */

	/* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
* @brief Reports the name of the source file and the source line number
* where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t *file, uint32_t line)
{
/* USER CODE BEGIN 6 */
/* User can add his own implementation to report the file name and line number,
tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
