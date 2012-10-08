#ifndef SERIALRXTHREAD_H
#define SERIALRXTHREAD_H

#include <QThread>
#ifndef Q_OS_WIN32
#define HANDLE int
#endif
#ifdef Q_OS_WIN32
#include <windows.h>
#endif
class SerialRXThread : public QThread
{
	Q_OBJECT
public:
	explicit SerialRXThread(QObject *parent = 0);	
	~SerialRXThread();
	void start(HANDLE handle);
private:
	bool m_terminate;
	HANDLE m_portHandle;
protected:
	void run();
signals:
	void incomingPacket(QByteArray packet);
	void dataWritten(QByteArray data);
	void dataRead(QByteArray data);
public slots:
	
};

#endif // SERIALRXTHREAD_H