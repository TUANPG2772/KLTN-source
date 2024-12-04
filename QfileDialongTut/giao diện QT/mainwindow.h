#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_btnClear_clicked();
    void on_btnLoad_clicked();
    void on_btnSave_clicked();

    void on_btn_temp_clicked();

    void on_pushButton_4_clicked();

   // void on_btn_state_clicked();

   // void on_btn_getTemp_clicked();
    
   // void on_btn_getState_clicked();
    
    void on_btnLoad2_clicked();

    void on_result_temp_clicked();

    void on_result_state_clicked();

    void on_btnsave1_clicked();

    void on_btnOpenDoor_clicked();

    void on_btnCloseDoor_clicked();

    void on_btnchangepassword_clicked();
    void readFromUART();

private:
    Ui::MainWindow *ui;
    struct LongestSubstringResult {
        int length;
        QString substring;
    };
    int uart_filestream;

    void uart_send(const char *message);
    int uart_receive(char *buffer, int buffer_size);
    LongestSubstringResult LengthOfLongestString(const QString &s); // Khai báo hàm LengthOfLongestString
};

#endif // MAINWINDOW_H
