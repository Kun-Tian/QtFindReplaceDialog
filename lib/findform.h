#ifndef FINDFORM_H
#define FINDFORM_H

#include <QWidget>
#include <QTextCursor>

namespace Ui {
    class FindForm;
}

class QTextEdit;

class FindForm : public QWidget {
    Q_OBJECT
public:
    FindForm(QWidget *parent = 0);
    ~FindForm();

    /**
      * Associates the text editor where to perform the search
      * @param textEdit_
      */
    void setTextEdit(QTextEdit *textEdit_) { textEdit = textEdit_; }

protected:
    void changeEvent(QEvent *e);

protected slots:
    /// performs the find task
    void find();

    /// when the text edit contents changed
    void textToFindChanged();

    /// checks whether the passed text is a valid regexp
    void validateRegExp(const QString &text);

private:
    Ui::FindForm *ui;

    /// for searching into the text
    QTextCursor textCursor;

    /// the text editor (possibly) associated with this form
    QTextEdit *textEdit;
};

#endif // FINDFORM_H
