//
// Created by Kal on 24/02/2024.
//

#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QTextEdit>

class AddGameDialog : public QDialog {
    Q_OBJECT
public:
    AddGameDialog(QWidget* parent);

public slots:
    int exec() override;
    void verify();
    void accept() override;

public:
    QString name() const;
    QString desc() const;
    QStringList genre() const;

private:
    static void populateGenreList(QListWidget* genreList);

    QLabel* nameLabel;
    QLineEdit* nameLineEdit;

    QLabel* descLabel;
    QTextEdit* descTextEdit;

    QLabel* genreLabel;
    QListWidget* genreList;

    QDialogButtonBox* buttonBox;
};

#endif // ADDGAMEDIALOG_H
