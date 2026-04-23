/*******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the
* 			   Sequence Validation and Generation Project using PSOC6
*              for ModusToolbox.
*
*
*
*******************************************************************************
* Copyright 2021-2024, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/



/*******************************************************************************
* Header Files
*******************************************************************************/
#if defined (CY_USING_HAL)
#include "cyhal.h"
#endif
#include "cybsp.h"
#include "cy_retarget_io.h"
#include "matrix_keypad.h"



/******************************************************************************
* Macros
*******************************************************************************/
#define KEYPAD_ROWS 4
#define KEYPAD_COLUMNS 4
#define ARRAY_SIZE 6
#define ENTER_KEY 'D'



/*******************************************************************************
* Global Variables
*******************************************************************************/
 char keymap[KEYPAD_ROWS][KEYPAD_COLUMNS] =
 {{'1','2','3','4'},   //key of the first row first column is '1'
 {'5','6','7','8'},   //key of the second row first column is '5'
 {'9','0','A','B'},   //key of the third row first column is '9'
 {'C','D','E','F'}};   //key of the fourth row first column is 'C'

 int i;



/*******************************************************************************
* Function Prototypes
*******************************************************************************/

void sequence_verification(unsigned int *arr);



/*******************************************************************************
* Function Definitions
*******************************************************************************/

void sequence_verification(unsigned int *arr)
{
	unsigned char expected;

    for(int i = 3; i < ARRAY_SIZE; i++)
    {
        expected = arr[i-2] + arr[i-3];

        if(arr[i] != expected)
        {
        	printf("Invalid sequence\n\r");
        	return;
        }
    }

    printf("Sequence is VALID\n");

	// compute next 3 numbers
	unsigned char next1 = arr[ARRAY_SIZE-2] + arr[ARRAY_SIZE-3];
	unsigned char next2 = arr[ARRAY_SIZE-1] + arr[ARRAY_SIZE-2];
	unsigned char next3 = next1 + arr[ARRAY_SIZE-1];

	printf("Next sequence: %d, %d, %d\n\r", next1, next2, next3);
}

/*******************************************************************************
* Function Name: main
*********************************************************************************
* Summary:
* This is the main function for CPU. It...
*    1.
*    2.
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    cy_rslt_t result;
    unsigned int character[ARRAY_SIZE];


    //loop variables
    int index = 0;

	#if defined (CY_DEVICE_SECURE) && defined (CY_USING_HAL)
		cyhal_wdt_t wdt_obj;

		/* Clear watchdog timer so that it doesn't trigger a reset */
		result = cyhal_wdt_init(&wdt_obj, cyhal_wdt_get_max_timeout_ms());
		CY_ASSERT(CY_RSLT_SUCCESS == result);
		cyhal_wdt_free(&wdt_obj);
	#endif

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();
    cy_retarget_io_init_fc(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,CYBSP_DEBUG_UART_CTS,CYBSP_DEBUG_UART_RTS,CY_RETARGET_IO_BAUDRATE);
    printf("\x1b[2J\x1b[;H");
    



	cyhal_gpio_t rowPins[] = {P9_0, P9_1, P9_2, P9_3};
	cyhal_gpio_t colPins[] = {P10_0, P10_1, P10_2, P10_3};


	for(int r=0;r<4;r++)
	{
	    cyhal_gpio_init(rowPins[r], CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, 1);
	}

	for(int c=0;c<4;c++)
	{
	    cyhal_gpio_init(colPins[c], CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_PULLUP, 1);
	}

    matrix_keypad_init((char*)keymap , rowPins, colPins, KEYPAD_ROWS, KEYPAD_COLUMNS);

    for(;;)
    {
        static char digit_buffer[3] = {0};
		static int digit_index = 0;

		matrix_keypad_scan();

		if(matrix_keypad_hasKey() == 1)
		{
			char k = matrix_keypad_getKey();
			printf("Key pressed: %c\n\r", k);

			// 1. If numeric key, store digit
			if(k >= '0' && k <= '9')
			{
				if(digit_index < 2)
				{
					digit_buffer[digit_index++] = k;
				}
				else
				{
					printf("Max 2 digits allowed!\n\r");
				}
			}

			// 2. ENTER key finalizes the number
			else if(k == ENTER_KEY)
			{
				if(digit_index == 0)
				{
					printf("Nothing to enter\n\r");
				}
				else
				{
					digit_buffer[digit_index] = '\0';

					int number = atoi(digit_buffer);   // convert to decimal

					printf("Entered number: %d\n\r", number);

					digit_index = 0;               // reset buffer
					memset(digit_buffer, 0, 3);

					// Store number in array
					if(index < ARRAY_SIZE)
					{
						character[index] = number;
						index++;

						if(index == ARRAY_SIZE)
						{
							sequence_verification(character);
							index = 0;
							printf("Press %d numbers...\n\n\r", ARRAY_SIZE);
						}
					}
				}
			}

			// 3. Ignore other keys
			else
			{
				printf("Invalid key\n\r");
			}

			cyhal_system_delay_ms(50);


			}
	}

}


/* [] END OF FILE */
