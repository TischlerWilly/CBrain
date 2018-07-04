#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clear();
    this->setWindowState(Qt::WindowMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::clear()
{
    isvalid = true;
    ini.clear();
    ui_rechte_nobody();
}

bool MainWindow::setup()
{
    isvalid = true;

    read_inifile();

    if(isvalid == true)
    {
        //Datei mit Benutzern suchen:
        read_iniuser();

        on_actionBenutzer_wechsen_triggered();
    }

    return isvalid;
}

void MainWindow::on_actionBenutzer_wechsen_triggered()
{
    //Anmeldedialog:
    Dialog_login *login = new Dialog_login;
    connect(login, SIGNAL(signal_ok(QString,QString)),       \
            this, SLOT(slot_login(QString,QString))     );
    login->exec();
    delete login;
}

void MainWindow::slot_login(QString user, QString pwd)
{
    if(u.login(user, pwd) == true)
    {
        if(u.is_admin() == true)
        {
            ui_rechte_admin();
        }else
        {
            ui_rechte_nobody();
        }
        this->setWindowTitle("CBrain /" + user);
    }else
    {
        ui_rechte_nobody();
        this->setWindowTitle("CBrain / Nobody");
    }
}

void MainWindow::read_inifile()
{
    QString filename = INIFILE;
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ini.set_text( file.readAll()  );
    }else
    {
        on_actionNetzwerkordner_aendern_triggered();

        if(isvalid == true)
        {
            //Inifile anlegen:
            if(file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                file.write(ini.get_rootdir().toUtf8());
                file.close();
            }else
            {
                QMessageBox mb;
                mb.setText("Fehler beim Zugriff auf INI-Datei!\nProgramm wird beendet.");
                mb.exec();
                isvalid = false;
            }
        }
    }
}

void MainWindow::write_inifile()
{
    QString filename = INIFILE;
    QFile file(filename);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(ini.get_text().toUtf8());
        file.close();
    }
}

void MainWindow::read_iniuser()
{
    QString filename;
    filename =  ini.get_rootdir();
    filename += QDir::separator();
    filename += INIUSER;
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        u.set_users(file.readAll());
        file.close();
    }
}

void MainWindow::write_iniuser()
{
    QString filename;
    filename =  ini.get_rootdir();
    filename += QDir::separator();
    filename += INIUSER;
    QFile file(filename);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        file.write(u.get_users().toUtf8());
        file.close();
    }
}

void MainWindow::on_actionNetzwerkordner_aendern_triggered()
{
    QString tmpdir;

    if(ini.get_rootdir().isEmpty())
    {
        tmpdir = "./";
    }else
    {
        tmpdir = ini.get_rootdir();
    }

    tmpdir = QFileDialog::getExistingDirectory(this, tr("Wurzelverzeichnis bestimmen"), tmpdir);
    if(!tmpdir.isEmpty())
    {
        ini.set_rootdir(tmpdir);
        write_inifile();
    }else
    {
        if(ini.get_rootdir().isEmpty())
        {
            QMessageBox mb;
            mb.setText("Wurzelverzeichnis nicht bekannt!\nProgramm wird beendet.");
            mb.exec();
            isvalid = false;
        }
    }
}

void MainWindow::on_actionBenutzer_verwalten_triggered()
{
    Dialog_user *d = new Dialog_user;
    connect(d, SIGNAL(signal_send_users(users)),        \
            this, SLOT(slot_get_users(users))           );
    d->set_users(u);
    d->exec();
    delete d;
}

void MainWindow::slot_get_users(users new_users)
{
    u = new_users;
    write_iniuser();
}

void MainWindow::on_actionInfo_triggered()
{
    QString msg;
    msg += "CBrain Version ";
    msg += VERSIONSNUMMER;
    msg += "\n";
    msg += "Autor: Oliver Schuft";
    msg += "\n";
    msg += "Quellcode: https://github.com/TischlerWilly/CBrain.git";
    //msg += "\n";

    QMessageBox mb;
    mb.setText(msg);
    mb.exec();
}

void MainWindow::on_actionProgrammeigene_Datenbank_triggered()
{
    Dialog_settings_db *d = new Dialog_settings_db;
    connect(d, SIGNAL(signal_send_data(text_zeilenweise)),           \
            this, SLOT(slot_get_settings_db_eigen(text_zeilenweise)) );
    d->set_data(ini.get_settings_db_eigen());
    d->exec();
    delete d;
}

void MainWindow::slot_get_settings_db_eigen(text_zeilenweise data)
{
    ini.set_settings_db_eigen(data);
    write_inifile();
}

//-----------------------------------------------UI den Rechten entsprechend anpassen:
void MainWindow::ui_rechte_nobody()
{
    ui->actionNetzwerkordner_aendern->setDisabled(true);
    ui->actionBenutzer_verwalten->setDisabled(true);
    ui->actionProgrammeigene_Datenbank->setDisabled(true);
}

void MainWindow::ui_rechte_admin()
{
    ui->actionNetzwerkordner_aendern->setEnabled(true);
    ui->actionBenutzer_verwalten->setEnabled(true);
    ui->actionProgrammeigene_Datenbank->setEnabled(true);
}

//-----------------------------------------------




