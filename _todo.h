#ifndef _TODO_H
#define _TODO_H
/*

template_Materialliste:
soll als Template zum Anlegen von neuen projektbezogenen Materiallisten dienen

-->Artikeltabelle erweitern
    ->Preis -->wird dann jedoch nicht als ID in Materialliste eingefügt, sondern als Kopie (Variierender Preis in den Aufträgen)
    ->Beziehung zu anderen Artiklen (Liste von Artiklen)
        ->Diese Artiklen werden Vorgeschlagen zum Mit-Bestellen
        ->id | default-Verhalten (mit bestellen/nur vorschlagen == checked/unchecked)

-->Interaktionen zwischen modul lager und modul bestellungen (noch nicht vorhanden)

-->user_A editiert ein Datenfeld
   user_B möchte auch editieren
   user_B bestätigt den dialog das user_A übergangen wird
   user_A kann nun die Änderung nicht mehr speichern
   wenn user_B nun jedoch dann nichts am Datansatz änder sondern mit cancel abbricht
   dann ist der Datensatz für die dannach folgende Änderung von user_A trotzdem noch blockiert
   wie den Knoten lösen?
   Wie user_A das speichern erlauben wenn user_B die Daten nicht verändert hat
   evtl Kopie des gesamten Datensatzes merken und vergleichen wenn datensatz nicht blockiert ist
   (block wird aufgehoben wenn user_B cancelt)
   dialog von user_A erwartet jedoch das die daten noch von ihm selbst blockiert sind

--> void Form_matlist::on_pushButton_pos_edit_rumpf_clicked()
    connect...

-->void Dialog_artikel::on_pushButton_beziehung_new_clicked()
-->void Dialog_artikel::on_pushButton_beziehung_delete_clicked()
-->void Dialog_artikel::on_pushButton_beziehung_edit_clicked()

-->Dialog-Schließen X oben rechts
    -->Funktion überladen auf btn_abbrechen
        ->weil block durch user wieder freigegeben werden muss!!

-->tr(...) für Ausgabe von Umlauten verwenden

-->Im-Export-Dialog




























*/
#endif // _TODO_H
