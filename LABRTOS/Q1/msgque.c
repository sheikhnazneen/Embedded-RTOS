//Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms.
 //Also create two additional task T4 and T5 where T4 sends integer data to T5 using Messsage Queues. Priorities of Tasks T1,T2,T3,T4,T5 are 5,6,7,8,9 respectively.

 #include<stdio.h>
 #include<freertos/FreeRTOS.h>
 #include<freertos/task.h>
 #include<freertos/timers.h>
 #include<freertos/queue.h>
 #include<freertos/semphr.h>

 #define QueueLength 4
 #define Itemsize 16

 TaskHandle_t task1Handle,task2Handle,task3Handle,task4Handle,task5Handle;
 QueueHandle_t q_t4_t5;
 
 void task1(void *data)
 {
    while(1)
    {
        printf("\n------ IN TASK 1-------\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
 }
void task2(void *data)
{
    while(1)
    {
        printf("\n---- IN TASK 2-------\n");
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void task3(void *data)
{
    while(1)
    {
        printf("\n---- IN TASK 3-------\n");
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void task4(void *data)
{
    BaseType_t send;
    int pdata =100;

    while(1)
    {
        pdata++;
        printf("\n-----IN TASK 4------\n");
        send = xQueueSend(q_t4_t5,&pdata,pdMS_TO_TICKS(1000));
        if(send == pdFALSE)
        {
            perror("Sending Failed\n");
        }
        else
        {
            printf("Pressure data sent to task 5\n");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void task5(void *data)
{
    int buffer;
    BaseType_t rec =0;
    while(1)
    {
        printf("\n-------IN TASK 5--------\n");
        rec = xQueueReceive(q_t4_t5,&buffer,pdMS_TO_TICKS(1000));
        if(rec==pdTRUE)
        {
            printf("Data received from Task 4: %d\n",buffer);
        }else{
            perror("Error in receiving data from Task 4.\n");
        }
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void app_main(void)
{
    BaseType_t res;
    printf("Starting maintask\n");
    q_t4_t5 = xQueueCreate(QueueLength,ItemSize);
    //create task 1
    res = xTaskCreate(task1,"Task1",2048,NULL,5,&task1Handle);
    if(res != pdPASS)
    {
        perror("Error in creating Task1.\n");
    }
    else{
        printf("Task1 created.\n");
    }

    //create task 2
    res = xTaskCreate(task2,"Task2",2048,NULL,6,&task2Handle);
    if(res!=pdPASS)
    {
        perror("Error in creating Task2.\n");
    }
    else{
        printf("Task2 created.\n");
    }
    //create task 3
    res = xTaskCreate(task3,"Task3",2048,NULL,6,&task3Handle);
    if(res!=pdPASS)
    {
        perror("Error in creating Task3.\n");
    }
    else{
        printf("Task3 created.\n");
    }
    //create task 4
    res = xTaskCreate(task4,"Task4",2048,NULL,6,&task4Handle);
    if(res!=pdPASS)
    {
        perror("Error in creating Task4.\n");
    }
    else{
        printf("Task4 created.\n");
    }
    //create task 5
    res = xTaskCreate(task5,"Task5",2048,NULL,6,&task5Handle);
    if(res!=pdPASS)
    {
        perror("Error in creating Task5.\n");
    }
    else{
        printf("Task5 created.\n");
    }
}