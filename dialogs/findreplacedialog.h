/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>

namespace Ui {
    class FindReplaceDialog;
}

class QTextEdit;
class QSettings;

/**
  * A find/replace dialog.
  */
class FindReplaceDialog : public QDialog {
    Q_OBJECT
public:
    FindReplaceDialog(QWidget *parent = 0);
    virtual ~FindReplaceDialog();

    /**
      * Associates the text editor where to perform the search
      * @param textEdit_
      */
    void setTextEdit(QTextEdit *textEdit);

    /**
      * Writes the state of the form to the passed settings.
      * @param settings
      * @param prefix the prefix to insert in the settings
      */
    virtual void writeSettings(QSettings &settings, const QString &prefix = "FindReplaceDialog");

    /**
      * Reads the state of the form from the passed settings.
      * @param settings
      * @param prefix the prefix to look for in the settings
      */
    virtual void readSettings(QSettings &settings, const QString &prefix = "FindReplaceDialog");

protected:
    void changeEvent(QEvent *e);

    Ui::FindReplaceDialog *ui;
};

#endif // FINDREPLACEDIALOG_H
