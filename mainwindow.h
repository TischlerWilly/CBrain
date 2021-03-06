#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define VERSIONSNUMMER  "1.2018.08.07"

#include <QMainWindow>
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include <QFileDialog>

#include "dialog_login.h"
#include "dialog_user.h"
#include "dialog_settings_db.h"

#include "form_tableeditor.h"
#include "form_artikel.h"
#include "form_lieferanten.h"
#include "form_lager.h"
#include "form_projekte.h"
#include "form_backup.h"
#include "form_personal.h"
#include "form_matlist.h"
#include "form_bestellung.h"

#include "defines_filenames.h"
#include "users.h"
#include "inifile.h"
#include "cbrainbatabase.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool setup();

signals:

protected:
    void resizeEvent(QResizeEvent *event);

public slots:
    void slot_login(QString user, QString pwd);
    void slot_get_users(users new_users);
    void slot_get_settings_db_eigen(text_zeilenweise data);
    void slot_write_inifile();
    void slot_setflag_matlist_proid(QString projektid);

private slots:
    void on_actionNetzwerkordner_aendern_triggered();
    void on_actionBenutzer_wechsen_triggered();
    void on_actionBenutzer_verwalten_triggered();
    void on_actionInfo_triggered();
    void on_actionProgrammeigene_Datenbank_triggered();
    void on_actionTestfunktion_triggered();
    void on_actionTabelleneditor_triggered();
    void on_actionKeinModul_triggered();
    void on_actionModulArtikel_triggered();
    void on_actionModulLieferanten_triggered();
    void on_actionModulLager_triggered();
    void on_actionModulBackup_triggered();
    void on_actionModulProjekte_triggered();
    void on_actionModulPersonal_triggered();
    void on_actionModulMaterialliste_triggered();
    void on_actionModulBestellungen_triggered();

private:
    Ui::MainWindow *ui;
    users u;
    //QString user;
    inifile ini;

    //Datenbanken:
    QSqlDatabase dbglobal;
    cbrainbatabase dbeigen;

    //Flags:
    bool isvalid;               //Anwendungsumgebung korrekt (Inifiles + Ordner...)
    QString currend_modul;      //Speichert den Namen des Moduls für WindowTitle
    QString flag_matlist_proid;

    //eigene Widgets:
    Form_tableeditor    *widget_tableeditor;
    Form_artikel        *widget_artikel;
    Form_lieferanten    *widget_lieferanten;
    Form_lager          *widget_lager;
    Form_projekte       *widget_projekte;
    Form_backup         *widget_backup;
    Form_personal       *widget_personal;
    Form_matlist        *widget_matlist;
    Form_bestellung     *widget_bestellung;

    //Funktionen:
    void clear();
    void read_inifile();
    void write_inifile();
    void read_iniuser();
    void write_iniuser();
    void ui_rechte_admin();
    void ui_rechte_nobody();
    void ui_rechte_modul_artikel(bool hat_rechte);
    void ui_rechte_modul_lieferanten(bool hat_rechte);
    void ui_rechte_modul_lager(bool hat_rechte);
    void ui_rechte_modul_projekte(bool hat_rechte);
    void ui_rechte_modul_perrsonal(bool hat_rechte);
    void ui_rechte_modul_matlist(bool hat_rechte);
    void ui_rechte_modul_bestellung(bool hat_rechte);

    void change_modul(QString modul);
    void change_windowtitle();

};

#endif // MAINWINDOW_H
