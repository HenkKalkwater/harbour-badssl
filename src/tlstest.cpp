#include "tlstest.h"

#include <QDebug>
#include <QNetworkRequest>

TlsTest::TlsTest(QObject *parent) : QObject(parent)
  , m_accessManager(new QNetworkAccessManager(this))
{
    connect(m_accessManager, &QNetworkAccessManager::sslErrors, this, &TlsTest::onSslErrors);
}

// NOOP
void TlsTest::classBegin() {}

void TlsTest::componentComplete() {
    runTest();
}
void TlsTest::onSslErrors(QNetworkReply *reply, const QList<QSslError> &errors) {
    Q_UNUSED(reply)
    m_errors.append(errors);
    emit errorsChanged();

    m_testSuccess = errors.size() == m_expectedErrors.size();
    if (m_testSuccess) {
        for (int i = 0; i < errors.size(); i++) {
            m_testSuccess &= static_cast<int>(errors.at(i).error()) == m_expectedErrors.at(i);
        }
    }
    qDebug() << errors;
    for (int i = 0; i < errors.size(); i++) {
        qDebug() << static_cast<int>(errors.at(i).error());
    }
    emit testSuccessChanged();
}

void TlsTest::runTest() {
    m_errors.clear();
    emit errorsChanged();

    qDebug() << m_expectedErrors;

    m_testRunning = true;
    emit testRunningChanged();
    QNetworkRequest request( (QUrl(m_url)) );
    auto reply = m_accessManager->get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply]() {
        if (m_expectedErrors.size() == 0) {
            m_testSuccess = m_errors.size() == 0;
            emit testSuccessChanged();
        }
        m_testRunning = false;
        emit testRunningChanged();
        reply->deleteLater();
    });
}

QStringList TlsTest::errors() const {
    QStringList result;
    for (auto it = m_errors.begin(); it != m_errors.end(); it++) {
        result.append(it->errorString());
    }
    return result;
}
