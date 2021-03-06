#ifndef FORM_PROJEKTE_H
#define FORM_PROJEKTE_H

#include <QWidget>

#include "cbrainbatabase.h"
#include "_tabellennamen.h"
#include "_tabname_personal.h"
#include "_tabname_projekt.h"
#include "_tabname_promat.h"
#include "_tabname_promatposlist.h"
#include "_tabname_promatpos.h"
#include "dialog_dataselection.h"
#include "text.h"
#include "datum.h"
#include "dialog_yes_no.h"
#include "dialog_projekte.h"
#include "users.h"

namespace Ui {
class Form_projekte;
}

class Form_projekte : public QWidget
{
    Q_OBJECT

public:
    explicit Form_projekte(QWidget *parent = 0);
    ~Form_projekte();

    void set_db(cbrainbatabase *new_db);
    void set_user(QString u);
    void set_user(users *users);
    void show();

public slots:
    void slot_new(text_zeilenweise data);
    void slot_delete(text_zeilenweise ids);
    void slot_edit_dialog(text_zeilenweise ids);
    void slot_edit_dialog();
    void slot_edit_dialog_cancel();
    void slot_edit(text_zeilenweise data, QString id);

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_pushButton_new_clicked();
    void on_pushButton_del_clicked();
    void on_pushButton_edit_clicked();
    void on_lineEdit_suche_textChanged();

private:
    Ui::Form_projekte *ui;

    cbrainbatabase *dbeigen;
    QSqlQueryModel *model;
    users *u;
    QString user;
    QString idbuffer;       //Speichert id
                            //von void slot_edit_dialog(text_zeilenweise ids);
                            //für void slot_edit_dialog();

    void update_table();
    void create_table_promat(QString project_id);
};

#endif // FORM_PROJEKTE_H
