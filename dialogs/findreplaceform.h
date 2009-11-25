/*
 * Copyright (C) 2009  Lorenzo Bettini <http://www.lorenzobettini.it>
 * See COPYING file that comes with this distribution
 */

#ifndef FINDREPLACEFORM_H
#define FINDREPLACEFORM_H

#include <QWidget>
#include <QTextCursor>

#include "findreplace_global.h"

namespace Ui {
    class FindReplaceForm;
}

class QTextEdit;
class QSettings;

/**
  * The form for the find/replace dialog
  */
class FINDREPLACESHARED_EXPORT FindReplaceForm : public QWidget {
    Q_OBJECT
public:
    FindReplaceForm(QWidget *parent = 0);
    virtual ~FindReplaceForm();

    /**
      * Associates the text editor where to perform the search
      * @param textEdit_
      */
    void setTextEdit(QTextEdit *textEdit_) { textEdit = textEdit_; }

    /// hides replace widgets from the form
    void hideReplaceWidgets();

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

    /**
     * performs the find task
     * @param down whether to find the next or the previous
     * occurrence
     */
    void find(bool down);

    /**
     * Finds the next occurrence
     */
    void findNext() { find(true); }

    /**
     * Finds the previous occurrence
     */
    void findPrev() { find(false); }

protected:
    void changeEvent(QEvent *e);

    /// shows an error in the dialog
    void showError(const QString &error);

protected slots:
    /**
     * performs the find task
     */
    void find();

    /// when the text edit contents changed
    void textToFindChanged();

    /// checks whether the passed text is a valid regexp
    void validateRegExp(const QString &text);

    /// the regexp checkbox was selected
    void regexpSelected(bool sel);

protected:
    Ui::FindReplaceForm *ui;

    /// for searching into the text
    QTextCursor textCursor;

    /// the text editor (possibly) associated with this form
    QTextEdit *textEdit;
};

#endif // FINDREPLACEFORM_H
