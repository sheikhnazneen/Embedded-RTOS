#include<stdio.h>
#include<freertos/FREERTOS.h>
#include<freertos/task.h>
#include<freertos/timers.h>

TaskHandle_t task1Handle,task2Handle,task3Handle;
TimerHandle_t oneShotTimer;
void callTimer(TimerHandle_t xTimer)
{
    printf("Timer Fired.Do ANY Functionality Here\n");
}
void task1(void *data)
{
    printf("Task1 started.\n");
    vTaskDelay(1000/portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}
void task2(void *data)
{
    printf("Task2 started.\n");
    vTaskDelay(2000/portTICK_PERIOD_MS);
    vTaskDelete(NULL);
}                     
void app_main(void)
{
    BaseType_t res;
    printf("Starting main task\n");
    oneShotTimer=xTimerCreate("Timer",pdMS_TO_TICKS(10000),pdTRUE,0,callTimer);
    //create task 1
    res=xTaskCreate(task1,"Task1",2048,NULL,5,&task1Handle);
    if(res != pdPASS)
    {
        perror("Error in creating Task1.\n");
    }
    else{
        printf("Task1 Created.\n");
    }
    //create task 2
    res = xTaskCreate(task2,"Task2",2048,NULL,6,&task2Handle);
    if(res!=pdPASS)
    {
        perror("Error in creating Task2.\n");
    }
    else{
        printf("Task2 Created.\n");
    }
    //create task 3
    res=xTaskCreate(task3,"Task3",2048,NULL,7,&task3Handle);
    if(res!=pdPASS)
    {
        perror("Error in creating Task3.\n");
    }
    else{
        printf("Task3 created.\n");
    }
}                     