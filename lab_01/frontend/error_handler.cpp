#include "error_handler.h"

void handle_error(result_code_t rc) //TODO переменные
{
    if (rc != ok)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Ошибка.");
        switch (rc)
        {
            case (error_open_file):
                msgBox.setText("Не удалость открыть файл!");
                msgBox.setInformativeText("Проверьте имя файла.");
                break;
            case (error_save_file):
                msgBox.setText("Не удалость сохранить файл!");
                msgBox.setInformativeText("Проверьте имя файла.");
                break;
            case (error_allocate_memory):
                msgBox.setText("Не удалось выделить память!");
                msgBox.setInformativeText("Закройте запущенные приложения.");
                break;
            case (error_empty_edit):
                msgBox.setText("Не удалось применить изменения!");
                msgBox.setInformativeText("Откройте файл для работы с ним.");
                break;
            case (error_empty_save):
                msgBox.setText("Не удалось сохранить файл!");
                msgBox.setInformativeText("Откройте файл для работы с ним.");
                break;
            case (error_read_file):
                msgBox.setText("Файл не соответствует формату!");
                msgBox.setInformativeText("Соответствующий программе формат файла (*.txt):\n"
                                          "x_центра y_центра z_центра\n"
                                          "количество_точек\n"
                                          "x_точки_1 y_точки_1 z_точки_1\n"
                                          "x_точки_2 y_точки_2 z_точки_2\n"
                                          "...\n"
                                          "количество_линий\n"
                                          "номер_начальной_точки номер_конечной_точки\n"
                                          "номер_начальной_точки номер_конечной_точки\n"
                                          "...");
                break;
            case (error_print_to_file):
                msgBox.setText("Ошибка записи в файл!");
                msgBox.setInformativeText("Проверьте права доступа или предоставьте другой файл!");
                break;
            case (error_broken_file):
                msgBox.setText("Ошибка чтения файла!");
                msgBox.setInformativeText("Неверные индексы в номерах точек!");
                break;
            case ok:
                break;
        }
        msgBox.exec();
    }
}
