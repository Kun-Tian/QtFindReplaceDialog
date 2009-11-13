/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#include <QtGui>
#include <QTextEdit>
#include <QRegExp>

#include "findreplaceform.h"
#include "ui_findreplaceform.h"

FindReplaceForm::FindReplaceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindReplaceForm), textEdit(0)
{
    ui->setupUi(this);

    ui->errorLabel->setText("");

    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(textToFindChanged()));
    connect(ui->textToFind, SIGNAL(textChanged(QString)), this, SLOT(validateRegExp(QString)));

    connect(ui->regexCheckBox, SIGNAL(toggled(bool)), this, SLOT(regexpSelected(bool)));

    connect(ui->findButton, SIGNAL(clicked()), this, SLOT(find()));
    connect(ui->closeButton, SIGNAL(clicked()), parent, SLOT(close()));
}

FindReplaceForm::~FindReplaceForm()
{
    delete ui;
}

void FindReplaceForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void FindReplaceForm::textToFindChanged() {
    ui->findButton->setEnabled(ui->textToFind->text().size() > 0);
}

void FindReplaceForm::regexpSelected(bool sel) {
    if (sel)
        validateRegExp(ui->textToFind->text());
    else
        validateRegExp("");
}

void FindReplaceForm::validateRegExp(const QString &text) {
    if (!ui->regexCheckBox->isChecked() || text.size() == 0) {
        ui->errorLabel->setText("");
        return; // nothing to validate
    }

    QRegExp reg(text,
                (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));

    if (reg.isValid()) {
        showError("");
    } else {
        showError(reg.errorString());
    }
}

void FindReplaceForm::showError(const QString &error) {
    if (error == "") {
        ui->errorLabel->setText("");
    } else {
        ui->errorLabel->setText("<span style=\" font-weight:600; color:#ff0000;\">" +
                                error +
                                "</spam>");
    }
}

void FindReplaceForm::find() {
    if (!textEdit)
        return; // TODO: show some warning?

    // backward search
    bool back = ui->upRadioButton->isChecked();

    const QString &toSearch = ui->textToFind->text();

    bool result = false;

    QTextDocument::FindFlags flags;

    if (back)
        flags |= QTextDocument::FindBackward;
    if (ui->caseCheckBox->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if (ui->wholeCheckBox->isChecked())
        flags |= QTextDocument::FindWholeWords;

    if (ui->regexCheckBox->isChecked()) {
        QRegExp reg(toSearch,
                    (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive));

        qDebug() << "searching for regexp: " << reg.pattern();

        textCursor = textEdit->document()->find(reg, textCursor, flags);
        textEdit->setTextCursor(textCursor);
        result = (!textCursor.isNull());
    } else {
        qDebug() << "searching for: " << toSearch;

        result = textEdit->find(toSearch, flags);
    }

    if (result)
        showError("");
    else
        showError(tr("no match found"));
}

