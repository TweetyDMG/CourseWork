#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <math.h> //для расчёта формул
#include <conio.h> //для getch()
#include <windows.h> //для system("cls")

#define M_PI 3.14159265358979323846

typedef struct
{
    double meshLength; 
    double meshWidth;
} mesh;
typedef struct
{
    double fenceLength;
    double stepHeight;  
    double stepWidth;
    int stepAmount;
    double dist_rods;
} lader;

int rods_ladder_output(lader *objectsLader, int *numLader, double *result_rods, int *numResult_rods);
int mesh_ladder_output(mesh *objectsMesh, lader *objectsLader, int *numMesh, int *numLader, int *result_mesh, int *numResult_mesh);
int save_to_file(char* filename, lader *objectsLader, int numLader, mesh *objectsMesh, int numMesh, double *result_rods, int numResultRods, int *result_mesh, int numResultMesh);

double rods_ladder_calc(const lader *objectsLader, int numLader);
int mesh_ladder_calc(const mesh *objectsMesh, const lader *objectsLader, int numLader, int numMesh);

int main() 
{
    setlocale(LC_CTYPE, "RUS");

    mesh objectsMesh[100];
    int numMesh = 0;

    lader objectsLader[100];
    int numLader = 0;

    double result_rods[100];
    int numResult_rods = 0;

    int result_mesh[100];
    int numResult_mesh = 0;

    char filename[100];
    char loadFilename[100];
    char menu, materialChoiceBalcony, materialChoiceLader, outputObjects, outputResult;
    printf("\n");
    printf("Вас приветствует программа для расчёта длины прута или количества рулонов сетки для ограждения лестницы с учетом её размеров.\n");

    do
    {  
    printf("\nМеню:\n");
    printf("1. Ввести данные для расчёта\n");
    printf("2. Просмотр существующих объектов и работа с файлом\n");
    printf("0. Завершить программу\n\n");
    printf("--Нажмите на клавишу с нужной цифрой для продолжения--");
    menu = getch();
    system("cls");

    switch (menu)
    {
    case '1':
        printf("\nВыберите вид строительного материала для лестницы:\n\n");
        printf("1. Прутья\n");
        printf("2. Сетка\n\n");
        printf("--Нажмите на клавишу с нужной цифрой для продолжения--\n\n");
        printf("--Для возвращения в главное меню нажмите на любую другую клавишу--");
        materialChoiceLader = getch();
        system("cls");
        switch (materialChoiceLader)
        {
            case '1':
            rods_ladder_output(objectsLader, &numLader, result_rods, &numResult_rods);
            break;

            case '2':
            mesh_ladder_output(objectsMesh, objectsLader, &numMesh, &numLader, result_mesh, &numResult_mesh);
            break;
        }
        break;
        

    case '2':
        do
        {
        printf("\nМеню для просмотра объектов и работы с файлом\n\n");

        printf("1. Созданные лестницы\n");
        printf("2. Созданные сетки\n");
        printf("3. Результаты расчётов\n");
        printf("4. Сохранить данные в файл\n");
        printf("0. Назад\n\n");
        printf("--Нажмите на клавишу с нужной цифрой для продолжения--\n");
        outputObjects = getch();
        system("cls");

        switch(outputObjects)
        { 
            case '1':
                if (numLader == 0)
                { 
                printf("Нет созданных лестниц.\n\n");
                printf("--Для продлжения нажмите любую клавишу--\n");
                getch();
                system("cls");
                }
                else 
                {
                printf("\nИнформация о существующих лестницах:\n");
                for (int i = 0; i < numLader; i++) 
                {
                    printf("\nЛестница %d\n\n", i + 1);
                    printf("Высота ограждения: %.2lf\n", objectsLader[i].fenceLength);
                    printf("Высота ступеньки: %.2lf\n", objectsLader[i].stepHeight);
                    printf("Ширина ступеньки: %.2lf\n", objectsLader[i].stepWidth);
                    printf("Количество ступенек: %d\n\n", objectsLader[i].stepAmount);                   
                }
                    printf("\n");
                    printf("--Для продолжения нажмите любую клавишу--\n");
                    getch();
                    system("cls"); 
                }
            break;

            case '2':
                if (numMesh == 0) {
                    printf("Нет созданных сеток.\n\n");
                    printf("--Для продлжения нажмите любую клавишу--\n");
                    getch();
                    system("cls");
                }  
                else 
                {
                    printf("\nИнформация о существующих сетках:\n");
                    for (int i = 0; i < numMesh; i++) 
                    {
                        printf("\nCетка %d\n\n", i + 1);
                        printf("Длина сетки в рулоне: %.2lf\n", objectsMesh[i].meshLength);
                        printf("Ширина сетки в рулоне: %.2lf\n\n", objectsMesh[i].meshWidth);
                    }
                    printf("--Для продолжения нажмите любую клавишу--\n");
                    getch();
                    system("cls"); 
                }
            break;

            case '3':
                
                printf("Выберете, что хотите увидеть\n\n");
                printf("1. Результаты при расчёте длины прута\n");
                printf("2. Результаты при расчёте количества рулонов сетки\n\n");
                printf("--Нажмите на клавишу с нужной цифрой для продолжения--\n");
                outputResult = getch();
                system("cls");
                switch(outputResult){
                case '1':

                if (numResult_rods == 0) {
                    printf("Вы ещё не вводили данные для расчётов\n\n");
                    printf("--Для продлжения нажмите любую клавишу--\n");
                    getch();
                    system("cls");
                }  
                else 
                {
                    for (int i = 0; i < numResult_rods; i++) 
                    {
                    printf("\nДанные %d:\n\n", i + 1);
                    printf("Высота ограждения: %.2lf\n", objectsLader[i].fenceLength);
                    printf("Высота ступеньки: %.2lf\n", objectsLader[i].stepHeight);
                    printf("Ширина ступеньки: %.2lf\n", objectsLader[i].stepWidth);
                    printf("Количество ступенек: %d\n", objectsLader[i].stepAmount);
                    printf("Расстояние между прутьями: %.2lf\n\n", objectsLader[i].dist_rods);
                    printf("~~ Результат расчётов: %.2lf метров прута ~~\n", result_rods[i]);
                    printf("-----------------------\n\n"); 
                    }
                    printf("--Для продолжения нажмите любую клавишу--\n");
                    getch();
                    system("cls");
                    break;
                    }

                case '2':

                    if (numResult_mesh == 0) {
                    printf("\nВы ещё не вводили данные для расчётов\n\n");
                    printf("--Для продлжения нажмите любую клавишу--\n");
                    getch();
                    system("cls");
                }  
                else 
                {
                    for (int i = 0; i < numResult_mesh; i++) 
                    {
                    printf("\nДанные %d:\n\n", i + 1);
                    printf("Длина сетки в одном рулоне: %0.2lf м.\n", objectsMesh[i].meshLength);
                    printf("Ширина сетки в рулоне: %0.2lf м.\n", objectsMesh[i].meshWidth);
                    printf("Высота ограждения: %0.2lf м.\n", objectsLader[i].fenceLength);
                    printf("Высота ступеньки: %0.2lf м.\n", objectsLader[i].stepHeight);
                    printf("Ширина ступеньки: %0.2lf м.\n", objectsLader[i].stepWidth);
                    printf("Количество ступенек: %d\n", objectsLader[i].stepAmount);
                    printf("~~ Результат расчётов: %d рулонов сетки ~~\n", result_mesh[i]);
                    printf("-----------------------\n\n"); 
                    }
                    printf("--Для продолжения нажмите любую клавишу--\n");
                    getch();
                    system("cls");
                    break;
                    }

                break;


                }
            break;



            case '4':
            if (numLader == 0 || numMesh == 0 || numResult_mesh == 0 || numResult_rods == 0){
                printf("\nНет данных для записи в файл.\n\n");
                printf("--Для продолжения нажмите любую клавишу--\n");
                getch();
                system("cls");
                
            }
                else{
                printf("Введите название файла для сохранения данных: ");
                scanf("%s", filename);
                save_to_file(filename, objectsLader, numLader, objectsMesh, numMesh, result_rods, numResult_rods, result_mesh, numResult_mesh);
                }
                break;

            case '0':
                break;

            default:
                printf("Вы нажали не ту клавишу. Попробуйте ещё раз\n");
                break;}
                } while(outputObjects != '0');
    break;
        
    default:
        printf("Вы нажали не ту клавишу. Попробуйте ещё раз\n");
        break;
    }
    }
    while(menu != '0');
    return 0;
}


int rods_ladder_output(lader *objectsLader, int *numLader, double *result_rods, int *numResult_rods)
{
        char confirmation;
        double result;
         do {
        printf("\nВведите высоту ограждения от поверхности ступеньки (в метрах): ");
        if (scanf("%lf", &objectsLader[*numLader].fenceLength) != 1 || objectsLader[*numLader].fenceLength <= 0) {
            printf("Ошибка ввода. Введите корректное значение\n\n");
            while (getchar() != '\n'); //очистка буфера для корректного ввода следующих данных
            continue;
        }
        printf("-------------------------");


        printf("\nВведите высоту ступеньки: ");
        if (scanf("%lf", &objectsLader[*numLader].stepHeight) != 1 || objectsLader[*numLader].stepHeight <= 0) {
            printf("Ошибка ввода. Введите корректное значение\n");
            while (getchar() != '\n');
            continue;
        }
        printf("-------------------------");


        printf("\nВведите ширину ступеньки (в метрах): ");
        if (scanf("%lf", &objectsLader[*numLader].stepWidth) != 1 || objectsLader[*numLader].stepWidth <= 0) {
            printf("Ошибка ввода. Введите корректное значение\n");
            while (getchar() != '\n');
            continue;
        }
        printf("-------------------------");


        printf("\nВведите количество ступенек: ");
        if (scanf("%d", &objectsLader[*numLader].stepAmount) != 1 || objectsLader[*numLader].stepAmount <= 0) {
            printf("Ошибка ввода. Введите корректное значение\n");
            while (getchar() != '\n');
            continue;
        }
        printf("-------------------------");

        printf("\nВведите расстояние между прутьями: ");
        if (scanf("%lf", &objectsLader[*numLader].dist_rods) != 1 || objectsLader[*numLader].dist_rods <= 0) {
            printf("Ошибка ввода. Введите корректное значение\n");
            while (getchar() != '\n');
            continue;
        }
        printf("-------------------------");

        break;

    } while (1);
        
        system("cls");

        printf("\nВы ввели следующие данные:\n\n");
        printf("Высота ограждения: %0.2lf м.\n", objectsLader[*numLader].fenceLength);
        printf("Высота ступеньки: %0.2lf м.\n", objectsLader[*numLader].stepHeight);
        printf("Ширина ступеньки: %0.2lf\n", objectsLader[*numLader].stepWidth);
        printf("Количество ступенек: %d\n", objectsLader[*numLader].stepAmount);
        printf("Расстояние между прутьями: %.2lf\n\n", objectsLader[*numLader].dist_rods);

        do{
        printf("Подтвердите ввод (Нажмите на клавишу 1 для продолжения, клавиша 2 - Для отказа): ");
        confirmation = getch();
        if (confirmation != '1' && confirmation != '2') printf("Вы нажали не ту клавишу. Попробуйте ещё раз\n");
        }while (confirmation != '1' && confirmation != '2');
        system("cls");
        if (confirmation == '2')
        {
        objectsLader[*numLader].fenceLength = 0.0;
        objectsLader[*numLader].stepHeight = 0.0;
        objectsLader[*numLader].stepWidth = 0.0;
        objectsLader[*numLader].stepAmount = 0;
        objectsLader[*numLader].dist_rods = 0.0;
        printf("Ввод отменен.\n");
        return 0;
        }

        if (rods_ladder_calc(objectsLader, *numLader) == 1) {
            printf("Произошла ошибка. Проверьте данные и повторите ввод");
            objectsLader[*numLader].fenceLength = 0.0;
            objectsLader[*numLader].stepHeight = 0.0;
            objectsLader[*numLader].stepWidth = 0.0;
            objectsLader[*numLader].stepAmount = 0;
            objectsLader[*numLader].dist_rods = 0.0;
            return 1;
        }
        else
        {
            result_rods[*numResult_rods] = rods_ladder_calc(objectsLader, *numLader);
            printf("\nДля ограждения лестницы прутьями вам необходимо: %.2lf метров прута\n\n",  result_rods[*numResult_rods]);
            printf("--Ознакомится с результатами вы можете, перейдя во второй пункт главного меню--\n\n");
            printf("--Для продолжения нажмите любую клавишу--\n");
            getch();
            system("cls"); 
            (*numLader)++;
            (*numResult_rods)++;
            return 0;
        }
}

int mesh_ladder_output(mesh *objectsMesh, lader *objectsLader, int *numMesh, int *numLader, int *result_mesh, int *numResult_mesh)
{
        int result;
        char confirmation;
       
        do {
        printf("\nВведите длину сетки в одном рулоне (в метрах): ");
        if (scanf("%lf", &objectsMesh[*numMesh].meshLength) != 1 || objectsMesh[*numMesh].meshLength <= 0) {
            printf("Ошибка ввода. Введите корректное значение\n\n");
            while (getchar() != '\n');
            continue;
        }
        printf("-------------------------");
        printf("\nВведите ширину сетки в рулоне (в метрах): ");
        if (scanf("%lf", &objectsMesh[*numMesh].meshWidth) != 1 || objectsMesh[*numMesh].meshWidth <= 0) {
            printf("Ошибка ввода. Введите корректное значение\n\n");
            while (getchar() != '\n');
            continue;
        }
        printf("-------------------------");
        
        printf("\nВведите высоту ограждения от поверхности ступеньки (в метрах): ");
        if (scanf("%lf", &objectsLader[*numLader].fenceLength) != 1 || objectsLader[*numLader].fenceLength <= 0) {
            printf("Ошибка ввода. Введите корректное значение\n\n");
            while (getchar() != '\n');
            continue;
        }
        printf("-------------------------");

        printf("\nВведите высоту ступеньки (в метрах): ");
        if (scanf("%lf", &objectsLader[*numLader].stepHeight) != 1 || objectsLader[*numLader].stepHeight <= 0) {
            printf("Ошибка ввода. Введите корректное значение\n\n");
            while (getchar() != '\n');
            continue;
        }
        printf("-------------------------");

        printf("\nВведите ширину ступеньки (в метрах): ");
        if (scanf("%lf", &objectsLader[*numLader].stepWidth) != 1 || objectsLader[*numLader].stepWidth <= 0) {
            printf("Ошибка ввода. Введите корректное значение\n\n");
            while (getchar() != '\n');
            continue;
        }
        printf("-------------------------");

        printf("\nВведите количество ступенек: ");
        if (scanf("%d", &objectsLader[*numLader].stepAmount) != 1 || objectsLader[*numLader].stepAmount <= 0) {
            printf("Ошибка ввода. Введите корректное значение\n\n");
            while (getchar() != '\n');
            continue;
        }
        printf("-------------------------");

        break;

    } while (1);

    system("cls");


        printf("Вы ввели следующие данные:\n");
        printf("Длина сетки в одном рулоне: %0.2lf м.\n", objectsMesh[*numMesh].meshLength);
        printf("Ширина сетки в рулоне: %0.2lf м.\n", objectsMesh[*numMesh].meshWidth);
        printf("Высота ограждения: %0.2lf м.\n", objectsLader[*numLader].fenceLength);
        printf("Высота ступеньки: %0.2lf м.\n", objectsLader[*numLader].stepHeight);
        printf("Ширина ступеньки: %0.2lf м.\n", objectsLader[*numLader].stepWidth);
        printf("Количество ступенек: %d\n", objectsLader[*numLader].stepAmount);

        do{
        printf("Подтвердите ввод (Нажмите на клавишу 1 для продолжения, клавиша 2 - Для отказа): ");
        confirmation = getch();
        if (confirmation != '1' && confirmation != '2') printf("Вы нажали не ту клавишу. Попробуйте ещё раз\n");
        }while (confirmation != '1' && confirmation != '2');
        system("cls");
        if (confirmation == '2')
        {
        objectsMesh[*numMesh].meshLength = 0.0;
        objectsMesh[*numMesh].meshWidth = 0.0;
        objectsLader[*numLader].fenceLength = 0.0;
        objectsLader[*numLader].stepHeight = 0.0;
        objectsLader[*numLader].stepWidth = 0.0;
        objectsLader[*numLader].stepAmount = 0;
        printf("Ввод отменен.\n");
        return 0;
        }

        if (mesh_ladder_calc(objectsMesh, objectsLader, *numLader, *numMesh) == -1)
        {
            printf("Произошла ошибка 1. Проверьте данные и повторите ввод");
            objectsMesh[*numMesh].meshLength = 0.0;
            objectsMesh[*numMesh].meshWidth = 0.0;
            objectsLader[*numLader].fenceLength = 0.0;
            objectsLader[*numLader].stepHeight = 0.0;
            objectsLader[*numLader].stepWidth = 0.0;
            objectsLader[*numLader].stepAmount = 0;
            return 1;
        }
        else {
            result_mesh[*numResult_mesh] = mesh_ladder_calc(objectsMesh, objectsLader, *numLader, *numMesh);
            printf("\nВам понадобится %d рулонов сетки.\n\n", result_mesh[*numResult_mesh]);
            printf("--Ознакомится с результатами вы можете, перейдя во второй пункт главного меню--\n\n");
            printf("--Для продолжения нажмите любую клавишу--\n");
            getch();
            system("cls");
            (*numMesh)++;
            (*numLader)++;
            (*numResult_mesh)++;
            return 0; 
        }
}

double rods_ladder_calc(const lader *objectsLader, int numLader)
{
    double step_width = objectsLader[numLader].stepWidth;
    double fence_length = objectsLader[numLader].fenceLength;
    double dist_rods = objectsLader[numLader].dist_rods;
    double step_amount = objectsLader[numLader].stepAmount;

    double frac1_1, frac1, result_sqrt, frac3, result;

    frac1_1 = (step_width * step_width) + (2*step_width * fence_length) + step_width;
    frac1 = frac1_1 / (dist_rods+dist_rods);
    frac3 = (dist_rods*dist_rods)*((step_amount*step_amount)+(step_width*step_width));
    result_sqrt = sqrt((frac3/(step_width*step_width))-(dist_rods*dist_rods));
    result = frac1*result_sqrt*step_amount;
    if (result > 0) return result;
    else return 1;
}

int mesh_ladder_calc(const mesh *objectsMesh, const lader *objectsLader, int numLader, int numMesh)
{
    double step_height = objectsLader[numLader].stepHeight;
    double step_width = objectsLader[numLader].stepWidth;
    double fence_length = objectsLader[numLader].fenceLength;
    double step_amount = objectsLader[numLader].stepAmount;
    double mesh_length = objectsMesh[numMesh].meshLength;
    double mesh_width = objectsMesh[numMesh].meshWidth;

    double fencing_area, fencing_mesh;
    int result;

    fencing_area = ((2*step_height+fence_length)*step_width*step_amount)/2;
    fencing_mesh = mesh_length*mesh_width;
    result = ceil(fencing_area/fencing_mesh);
    if (result > 0) return result;
    else return -1;
}

int save_to_file(char* filename, lader *objectsLader, int numLader, mesh *objectsMesh, int numMesh, double *result_rods, int numResultRods, int *result_mesh, int numResultMesh)
{

    if (numLader == 0 && numMesh == 0) {
    printf("Нет объектов для сохранения.\n");
    return 1;
    }

    FILE* file = fopen(filename, "w");
    
    if (file == NULL) {
        printf("Не удалось открыть файл для записи.\n");
        return 1;
    }
    fprintf(file, "Данные с прутьями\n\n");
    for (int i = 0; i < numResultRods; i++) {
        fprintf(file, "\nДанные %d:\n\n", i + 1);
        fprintf(file, "Высота ограждения: %.2lf\n", objectsLader[i].fenceLength);
        fprintf(file, "Высота ступеньки: %.2lf\n", objectsLader[i].stepHeight);
        fprintf(file, "Ширина ступеньки: %.2lf\n", objectsLader[i].stepWidth);
        fprintf(file, "Количество ступенек: %d\n", objectsLader[i].stepAmount);
        fprintf(file, "Расстояние между прутьями: %.2lf\n\n", objectsLader[i].dist_rods);
        fprintf(file, "~~ Результат расчётов: %.2lf метров прута ~~\n", result_rods[i]);
        fprintf(file, "-----------------------\n\n"); 
    }
    fprintf(file, "~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

    fprintf(file, "Данные с сетками\n\n");
    for (int i = 0; i < numResultMesh; i++)
    {
        fprintf(file, "Данные %d:\n\n", i+1);
        fprintf(file, "Высота ступеньки: %.2lf\n", objectsLader[i].stepHeight);
        fprintf(file, "Ширина ступеньки: %.2lf\n", objectsLader[i].stepWidth);
        fprintf(file, "Количество ступенек: %d\n", objectsLader[i].stepAmount);
        fprintf(file, "Длина сетки в рулоне: %.2lf\n", objectsMesh[i].meshLength);
        fprintf(file, "Ширина сетки в рулоне: %.2lf\n", objectsMesh[i].meshWidth);
        fprintf(file, "~~ Результат расчётов: %d рулонов ~~\n", result_mesh[i]);
        fprintf(file, "-----------------------\n\n"); 
    }

    fclose(file);
    printf("Данные успешно сохранены в файл '%s'.\n", filename);
    return 0;
}

