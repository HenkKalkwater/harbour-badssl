#ifndef TLSTEST_H
#define TLSTEST_H

#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QPair>
#include <QQmlParserStatus>

class TlsTest : public QObject, public QQmlParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QQmlParserStatus);
    Q_PROPERTY(QString url MEMBER m_url NOTIFY urlChanged)
    Q_PROPERTY(QStringList errors READ errors NOTIFY errorsChanged)
    Q_PROPERTY(QList<int> expectedErrors MEMBER m_expectedErrors NOTIFY expectedErrorsChanged)
    Q_PROPERTY(bool testSuccess READ testSuccess NOTIFY testSuccessChanged)
    Q_PROPERTY(bool testRunning READ testRunning NOTIFY testRunningChanged)
public:
    explicit TlsTest(QObject *parent = nullptr);

    void classBegin() override;
    void componentComplete() override;

    void runTest();

    QStringList errors() const;
    bool testSuccess() const { return m_testSuccess; }
    bool testRunning() const { return m_testRunning; }
private slots:
    void onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
signals:
    void urlChanged();
    void errorsChanged();
    void expectedErrorsChanged();
    void testSuccessChanged();
    void testRunningChanged();
private:
    bool m_testSuccess = false;
    bool m_testRunning = false;
    QString m_url;
    QList<QSslError> m_errors;
    QList<int> m_expectedErrors;
    QNetworkAccessManager *m_accessManager;
};

#endif // TLSTEST_H
