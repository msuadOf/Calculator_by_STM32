/* USER CODE BEGIN Header */

/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include"u8g2.h"
#include <stdio.h>
#include<math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
u8g2_t u8g2;
//buffer starts
uint8_t first[14]={0};
uint8_t second[14]={0};
uint8_t resault[14]={0};
char menu[16][2]={
        "7","8","9","/",
        "4","5","6","x",
        "1","2","3","-",
        "0",".","=","+"
};
char sign[2];
uint8_t line=1;
uint8_t model=1;
uint8_t state=1;
//state表：
//  输入  1
//   +    2
//   -    3
//   x    4
//   /    5
//  输出  6
char byf250[20];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,
                                  U8X8_UNUSED uint8_t msg,
                                  U8X8_UNUSED uint8_t arg_int,
                                  U8X8_UNUSED void *arg_ptr);
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,void *arg_ptr);
int strlen(uint8_t *s);
char* strcat(char *destination,const char *source);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
typedef struct {
    GPIO_TypeDef *GPIOx;
    uint16_t GPIO_Pin;
} GPIO_Pin_TypeDef;

GPIO_Pin_TypeDef keyboardRow[] = {
        { KB_R3_GPIO_Port, KB_R3_Pin },
        { KB_R2_GPIO_Port, KB_R2_Pin },
        { KB_R1_GPIO_Port, KB_R1_Pin },
        { KB_R0_GPIO_Port, KB_R0_Pin },
};

GPIO_Pin_TypeDef keyboardCol[] = {
        { KB_C3_GPIO_Port, KB_C3_Pin },
        { KB_C2_GPIO_Port, KB_C2_Pin },
        { KB_C1_GPIO_Port, KB_C1_Pin },
        { KB_C0_GPIO_Port, KB_C0_Pin },
};

uint32_t KeyboardScan(void)
{
    uint32_t result = 0;
    for (int row = 0; row < sizeof(keyboardRow) / sizeof(GPIO_Pin_TypeDef); row++)
    {
        HAL_GPIO_WritePin(keyboardRow[row].GPIOx, keyboardRow[row].GPIO_Pin, GPIO_PIN_SET);
        for (int col = 0; col < sizeof(keyboardCol) / sizeof(GPIO_Pin_TypeDef); col++)
        {
            result <<= 1;
            result |= HAL_GPIO_ReadPin(keyboardCol[col].GPIOx, keyboardCol[col].GPIO_Pin) == GPIO_PIN_SET;
        }
        HAL_GPIO_WritePin(keyboardRow[row].GPIOx, keyboardRow[row].GPIO_Pin, GPIO_PIN_RESET);
    }

    return result;
}

//u8g2相关内容



void frame(u8g2_t* u8g2,uint8_t first[],uint8_t second[],uint8_t out[],uint8_t sign[]);
void frameutf8(u8g2_t* u8g2,uint8_t first[],uint8_t second[],uint8_t out[]);

uint8_t decode(uint16_t data,uint8_t pos);

void operate(uint8_t* first)
{
    uint32_t index=KeyboardScan();
//    loop:
//    if (!KeyboardScan())
//
//        for (int i = 0; i < 16; i++) {
//            if (index & (1 << i)) {
//                strcat(first, menu[i]);
//            }
//        }
//    else
//        goto loop;

while(KeyboardScan())
{

}
    for (int i = 0; i < 16; i++) {
        if (index & (1 << i)) {
            strcat(first, menu[i]);
        }
    }

//    for(int i=0;i<16;i++)//标记位i
//    {
//        if (decode(index, i) > 0)//按下就进行匹
//        {
//            switch (index) {
//                case 1:
//                    strcat(first, "7");
//                    state = 1;
//                    break;
//                case 2:
//                    strcat(first, "8");
//                    state = 1;
//                    break;
//                case 4:
//                    strcat(first, "9");
//                    state = 1;
//                    break;
//                case 8:
//                    //strcat(buffer,"7");
//                    state = _div;
//                    break;
//                case 16:
//                    strcat(first, "4");
//                    state = _input;
//                    break;
//                case 32:
//                    strcat(first, "5");
//                    state = _input;
//                    break;
//                case 64:
//                    strcat(first, "6");
//                    state = _input;
//                    break;
//                case 128:
//                    state = _multi;
//                    break;
//                case 256:
//                    strcat(first, "1");
//                    state = _input;
//                    break;
//                case 512:
//                    strcat(first, "2");
//                    state = _input;
//                    break;
//                case 1024:
//                    strcat(first, "3");
//                    state = _input;
//                    break;
//                case 2048:
//                    state = _sub;
//                    break;
//                case 4096:
//                    strcat(first, "0");
//                    state = _input;
//                    break;
//                case 8192:
//                    strcat(first, ".");
//                    state = _input;
//                    break;
//                case 16384:
//                    state = _output;
//                    break;
//                case 32768:
//                    state = _plus;
//                    break;
//            }
//        }
//    }
}
void countmodel(uint8_t *buffer)
{
    int i=0;
    while(buffer[i++])
    {
        if(buffer[i]=='.')
            model=_float;
    }
}
int str2value_int(uint8_t *buffer)
{
    int len = 0;
    int sum = 0;
    int i = 0;
    while (buffer[i++])
    {

        sum = sum * 10 + buffer[i-1] - '0';

    }
    return sum;
}
void value2str_int(uint8_t* buffer,int value)
{
    int m, len = 0;
    if (value >= 0)
    {
        do {
            m = value % 10;
            len = 0;
            while (buffer[len++]);
            len--;
            for (; len > 0; len--) {
                buffer[len] = buffer[len - 1];
            }
            buffer[0] = m + '0';
            value /= 10;

        } while (value);
    }
    else
    {
        value=-value;
        do {
            m = value % 10;
            len = 0;
            while (buffer[len++]);
            len--;
            for (; len > 0; len--) {
                buffer[len] = buffer[len - 1];
            }
            buffer[0] = m + '0';
            value /= 10;

        } while (value);
        len = 0;
        while (buffer[len++]);
        len--;
        for (; len > 0; len--) {
            buffer[len] = buffer[len - 1];
        }
        buffer[0] = '-';

    }

}

//copy de demo
float str2value_float(char *num){

    double n = 0, sign = 1, scale = 0;
    int subscale = 0, signsubscale = 1;

    if (*num == '-') {
        sign = -1, num++;	/* Has sign? */
    }

    while (*num == '0') {
        num++;
    }

    if (*num >= '1' && *num <= '9')	{
        do {
            n = (n * 10.0) + (*num++ - '0');
        } while (*num >= '0' && *num <= '9');	/* Number? */
    }

    if (*num == '.' && num[1] >= '0' && num[1] <= '9') {
        num++;
        do {
            n = (n * 10.0) + (*num++ -'0'), scale--;
        } while (*num >= '0' && *num <= '9');
    }	/* Fractional part? */

    if (*num == 'e' || *num == 'E')	{	/* Exponent? */
        num++;
        if (*num == '+') {
            num++;
        } else if (*num == '-') {
            signsubscale = -1, num++;		/* With sign? */
        }

        while (*num >= '0' && *num <= '9' ) {
            subscale = (subscale * 10) + (*num++ - '0');	/* Number? */
        }
    }

    n = sign * n * pow(10.0, (scale + subscale * signsubscale));	/* number = +/- number.fraction * 10^ +/- exponent */

    return n;
}
void value2str_float(char*buffer,float slope)  //浮点型数，存储的字符数组，字符数组的长度
{
   // buffer[0]=' ';
    int n= 13;
    int temp,i,j;
    if(slope<0)
    {
        buffer[0] = '-';
        slope = -slope;
    }
    temp = (int)slope;//取整数部分
    for(i=0;temp!=0;i++)//计算整数部分的位数
        temp /=10;
    temp =(int)slope;

    for(j=i;j>=0;j--)//将整数部分转换成字符串型
    {
        buffer[j] = temp%10+'0';
        temp /=10;
    }

    buffer[i+1] = '.';
    slope -=(int)slope;
    for(i=i+2;i<n-1;i++)//将小数部分转换成字符串型
    {
        slope*=10;
        buffer[i]=(int)slope+'0';
        slope-=(int)slope;
    }
    buffer[n-1] = '\0';
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
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
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
    u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay);
    u8g2_InitDisplay(&u8g2);
    u8g2_SetPowerSave(&u8g2, 0);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
      //HAL_UART_Transmit(&huart1,"hhh",3,HAL_MAX_DELAY);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//      uint32_t keyboard = KeyboardScan();
//
//      u8g2_FirstPage(&u8g2);
//      do
//      {
//          u8g2_SetFont(&u8g2, u8g2_font_courR18_tf);
//          u8g2_DrawStr(&u8g2, 60, 60, "SAST");
//
//          for (size_t i = 0; i < 4; i++)
//          {
//              for (size_t j = 0; j < 4; j++)
//              {
//                  if (keyboard & (1 << (15 - i * 4 - j)))
//                  {
//                      u8g2_DrawStr(&u8g2, j * 12, i * 16 - 1 + 16, "1");
//                  }
//                  else
//                  {
//                      u8g2_DrawStr(&u8g2, j * 12, i * 16 - 1 + 16, "0");
//                  }
//              }
//          }
//
//      } while (u8g2_NextPage(&u8g2));

//************uniform model select***********************


      int keyboard=KeyboardScan();

      for (int i = 0; i < 16; i++)
      {
          if (keyboard & (1 << i))
          {

              //***********select format******************

              if (menu[i][0]=='+')
              {
                state=_plus;
                sign[0]='+';
              }
              else if (menu[i][0]=='-')
              {
                state=_sub;
                sign[0]='-';
                  //HAL_UART_Transmit(&huart1,&menu[i],1,HAL_MAX_DELAY);
              }
              else if (menu[i][0]=='x')
              {
                state=_multi;
                  sign[0]='x';
              }
              else if (menu[i][0]=='/')
              {
                  state=_div;
                  sign[0]='/';
              }
              else if (menu[i][0]=='=')
              {
                  state=_output;

              }




              //************format end******************
          }
      }
//***************************************************************

      if (state == 1&&line==1)
          operate(first);
      else if (state >= 3)
      {
          state = _input;
          line = 2;
      }
      else if(state==1&&line==2)
          operate(second);
      else if(state==_output)
      {
          while(KeyboardScan())
          {

          }
      int one= str2value_int(first),two= str2value_int(second);

      if(sign[0]=='+')
          value2str_int(resault,one+two);
      if(sign[0]=='-')
          value2str_int(resault,one-two);
      if(sign[0]=='x')
          value2str_int(resault,one*two);
      if(sign[0]=='/')
          value2str_float(resault,(double)one/two);
          state=0;
      }



//else if(state);



      frame(&u8g2,first,second,resault,sign);

//      u8g2_FirstPage(&u8g2);
//      do {
//          u8g2_SetFont(&u8g2, u8g2_font_courR12_tf);
//
//          sprintf(byf250,"%d",state);
//          u8g2_DrawStr(&u8g2,1,45,byf250);
//
//      } while (u8g2_NextPage(&u8g2));

//    int index=KeyboardScan();
//      int len = strlen(resault);
//      u8g2_FirstPage(&u8g2);
//      do {
//          u8g2_SetFont(&u8g2, u8g2_font_courR12_tf);
//          u8g2_DrawStr(&u8g2, 0, 15, first);
//          u8g2_DrawStr(&u8g2, 0, 30, second);
////          u8g2_DrawStr(&u8g2, 128 - len * 10, 50, resault);
//          u8g2_DrawLine(&u8g2, 0, 32, 128, 32);
//          sprintf(byf250,"%d",index);
//          u8g2_DrawStr(&u8g2,1,45,byf250);
//
//      } while (u8g2_NextPage(&u8g2));
              
      //HAL_Delay(500);
          
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
uint8_t u8x8_stm32_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8,
                                  U8X8_UNUSED uint8_t msg,
                                  U8X8_UNUSED uint8_t arg_int,
                                  U8X8_UNUSED void *arg_ptr)
{
    switch (msg)
    {
        case U8X8_MSG_GPIO_AND_DELAY_INIT:
            HAL_Delay(1);
            break;
        case U8X8_MSG_DELAY_MILLI:
            HAL_Delay(arg_int);
            break;
        case U8X8_MSG_GPIO_DC:
            HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, arg_int);
            break;
        case U8X8_MSG_GPIO_RESET:
            HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, arg_int);
            break;
    }
    return 1;
}

uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,void *arg_ptr)
{
    switch (msg)
    {
        case U8X8_MSG_BYTE_SEND:
            HAL_SPI_Transmit(&hspi1, (uint8_t *) arg_ptr, arg_int, HAL_MAX_DELAY);
            break;
        case U8X8_MSG_BYTE_INIT:
            break;
        case U8X8_MSG_BYTE_SET_DC:
            HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, arg_int);
            break;
        case U8X8_MSG_BYTE_START_TRANSFER:
            HAL_GPIO_WritePin(OLED_NSS_GPIO_Port, OLED_NSS_Pin, GPIO_PIN_RESET);
            break;
        case U8X8_MSG_BYTE_END_TRANSFER:
            HAL_GPIO_WritePin(OLED_NSS_GPIO_Port, OLED_NSS_Pin, GPIO_PIN_SET);
            break;
        default:
            return 0;
    }
    return 1;
}
int strlen(uint8_t *s)
{
    int i=0;
    while(s[i])
    {
        i++;
    }
    return i;
}
char* strcat(char *destination,const char *source)
{
    int i=0;
    while(destination[i]!='\0')
        i++;
    while (*source!='\0')
        destination[i++]=*(source++);
    *(destination+i)='\0';
    return (destination);
}
void frameutf8(u8g2_t* u8g2,uint8_t first[],uint8_t second[],uint8_t out[])
{
    int len=strlen(out);
//    u8g2_FirstPage(u8g2);
//    do
//    {
//        u8g2_SetFont(u8g2, u8g2_font_courR12_tf);
//        u8g2_DrawStr(u8g2, 0, 15, first);
//        u8g2_DrawStr(u8g2, 0, 30, second);
//        u8g2_DrawStr(u8g2, 128-len*10, 50, out);
//        u8g2_DrawLine(u8g2,0, 32, 128, 32);
//
//
//    } while (u8g2_NextPage(u8g2));

    u8g2_FirstPage(u8g2);
    u8g2_ClearBuffer(u8g2);
    do
    {

        u8g2_SetFont(u8g2,u8g2_font_unifont_t_symbols);
        u8g2_DrawUTF8(u8g2, 0, 15, first);
        u8g2_DrawUTF8(u8g2, 0, 30, second);
        u8g2_DrawUTF8(u8g2, 128-len*10, 50, out);
        u8g2_DrawLine(u8g2,0, 32, 128, 32);
    } while (u8g2_NextPage(u8g2));
}
void frame(u8g2_t* u8g2,uint8_t first[],uint8_t second[],uint8_t out[],uint8_t sign[])
{
    int len=strlen(out);
    u8g2_FirstPage(u8g2);
    do
    {
        u8g2_SetFont(u8g2, u8g2_font_courR12_tf);
        u8g2_DrawStr(u8g2, 0, 15, first);
        u8g2_DrawStr(u8g2, 0, 30, second);
        u8g2_DrawStr(u8g2, 128-len*10, 50, out);
        u8g2_DrawStr(u8g2, 0, 50, sign);
        u8g2_DrawLine(u8g2,0, 32, 128, 32);


    } while (u8g2_NextPage(u8g2));
}
uint8_t decode(uint16_t data,uint8_t pos)
{
    return data&(1<<pos);
//    return 1&(data>>(pos));
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
