#ifndef FORM_MATLIST_H
#define FORM_MATLIST_H

#include <QWidget>

#include "cbrainbatabase.h"
#include "_tabellennamen.h"
#include "_tabname_projekt.h"
#include "_tabname_promat.h"
#include "_tabname_promatpos.h"
#include "_tabname_promatposlist.h"
#include "_tabname_personal.h"
#include "_tabname_status.h"
#include "_tabname_lieferant.h"
#include "dialog_dataselection.h"
#include "dialog_promatpos.h"
#include "dialog_promatposrumpf.h"
#include "text.h"
#include "dialog_yes_no.h"
#include "artikel_mengenerfassung.h"
#include "dialog_printbox.h"

namespace Ui {
class Form_matlist;
}

class Form_matlist : public QWidget
{
    Q_OBJECT

public:
    explicit Form_matlist(QWidget *parent = 0);
    ~Form_matlist();

    void set_db(cbrainbatabase *new_db);
    void set_user(QString u);
    void set_proid(QString projektid);

public slots:
    void slot_set_project(text_zeilenweise p);
    void slot_new_matpos(text_zeilenweise data);
    void slot_edit_matposlist(text_zeilenweise data, QString id);
    void slot_edit_matposlist();
    void slot_edit_matposlist_with_block();
    void slot_edit_matposlist_unblock();
    void slot_delete_matpos();
    void slot_update_table();
    void slot_import_get_projekt_id(text_zeilenweise ids);
    void slot_import_get_pos_id(text_zeilenweise ids);

signals:
    void signal_proidchanged(QString projektid);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_pushButton_projektauswahl_clicked();
    void on_lineEdit_projekt_id_textChanged(const QString &arg1);
    void on_pushButton_pos_new_clicked();
    void on_pushButton_pos_edit_clicked();
    void on_pushButton_pos_delete_clicked();
    void on_pushButton_check_all_pos_clicked();
    void on_pushButton_check_activ_pos_clicked();
    void on_pushButton_pos_edit_rumpf_clicked();
    void on_pushButton_update_table_clicked();
    void on_lineEdit_filter_textChanged();
    void on_checkBox_erfasst_toggled();
    void on_checkBox_unklar_toggled();
    void on_checkBox_bestellen_toggled();
    void on_checkBox_pos_status_toggled();
    void on_pushButton_pos_copy_clicked();
    void on_pushButton_pos_import_clicked();
    void on_checkBox_reserviert_toggled();
    void on_checkBox_einzelmengen_toggled();
    void on_checkBox_verarbeitet_toggled();
    void on_checkBox_show_pos_toggled(bool checked);
    void on_pushButton_reservieren_clicked();
    void on_pushButton_packliste_clicked();

private:
    Ui::Form_matlist *ui;
    cbrainbatabase *dbeigen;
    QSqlQueryModel *model;
    QString user;
    text_zeilenweise promatposlist_current_data;
    QString promatposlist_current_id;
    int promatpos_menge_vor;
    QString promat_tabname;
    QString import_projekt_id;

    void create_table_promatposlist();  //Tabelle die die Materialpositionen erfasst
    void create_table_promatpos(QString bez, QString menge); //Tabelle die den Inhalt einer Materialposition erfasst
    void update_listwidget_matpos();
    void update_table();
    void update_statusbar();
    void update_promatpos_mengen(QString pro_id, QString pos_id, double pos_me_vor, double pos_me_nach);
};

#endif // FORM_MATLIST_H
