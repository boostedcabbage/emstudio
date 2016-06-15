/************************************************************************************
 * EMStudio - Open Source ECU tuning software                                       *
 * Copyright (C) 2013  Michael Carpenter (malcom2073@gmail.com)                     *
 *                                                                                  *
 * This file is a part of EMStudio                                                  *
 *                                                                                  *
 * EMStudio is free software; you can redistribute it and/or                        *
 * modify it under the terms of the GNU Lesser General Public                       *
 * License as published by the Free Software Foundation, version                    *
 * 2.1 of the License.                                                              *
 *                                                                                  *
 * EMStudio is distributed in the hope that it will be useful,                      *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of                   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                *
 * Lesser General Public License for more details.                                  *
 *                                                                                  *
 * You should have received a copy of the GNU Lesser General Public                 *
 * License along with this program; if not, write to the Free Software              *
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   *
 ************************************************************************************/

#include "nitroussettingsview.h"
#include "QsLog.h"

NitrousSettingsView::NitrousSettingsView(bool isram, bool isflash,QWidget *parent)
{
	Q_UNUSED(parent)
	m_data = 0;
	ui.setupUi(this);
	connect(ui.saveToFlashButton,SIGNAL(clicked()),this,SLOT(saveFlashButtonClicked()));
	/*
	connect(ui.saveRamPushButton,SIGNAL(clicked()),this,SLOT(saveRamButtonClicked()));
	connect(ui.loadFlashPushButton,SIGNAL(clicked()),this,SLOT(loadFlashButtonClicked()));
	connect(ui.loadRamPushButton,SIGNAL(clicked()),this,SLOT(loadRamButtonClicked()));
	if (!isram)
	{
		//Is only flash
		ui.saveRamPushButton->setEnabled(false);
		ui.saveRamPushButton->setVisible(false);
		ui.loadRamPushButton->setEnabled(false);
		ui.loadRamPushButton->setVisible(false);
	}
	else if (!isflash)
	{
		//Is only ram
		ui.saveFlashPushButton->setEnabled(false);
		ui.saveFlashPushButton->setVisible(false);
		ui.loadFlashPushButton->setEnabled(false);
		ui.loadFlashPushButton->setVisible(false);
	}
	else
	{
		//Is both ram and flash, leave both sets of buttons enabled.
	}*/
}
void NitrousSettingsView::passDatalog(QVariantMap data)
{
	Q_UNUSED(data)
}
bool NitrousSettingsView::setData(unsigned short locationid,DataBlock *data)
{

	unsigned short temp = 0;
	float tempf = 0;
	m_data = (RawData*)(data);
	qba = m_data->data();
	unsigned char *tdata = (unsigned char *)qba.data();

	tempf = ((float)((tdata[82] << 8) + tdata[83]) / 1250);
	ui.lowRPMPulseWidthLineEdit->setText(QString::number(tempf));

	tempf = ((float)((tdata[84] << 8) + tdata[85]) / 1250);
	ui.highRPMPulseWidthLineEdit->setText(QString::number(tempf));

	temp = (((tdata[86] << 8) + tdata[87]) / 2);
	ui.enableRPMLineEdit->setText(QString::number(temp));

	temp = (((tdata[88] << 8) + tdata[89]) / 2);
	ui.disableRPMLineEdit->setText(QString::number(temp));

	temp = (((tdata[90] << 8) + tdata[91]) / 640);
	ui.enableTPSThresholdLineEdit->setText(QString::number(temp));

	temp = (((tdata[92] << 8) + tdata[93]) / 100);
	ui.disableKPAThresholdLineEdit->setText(QString::number(temp));


	/*if (m_data)
	{
		disconnect(m_data,SIGNAL(update()),this,SLOT(update()));
	}
	m_data = (RawData*)(data);
	connect(m_data,SIGNAL(update()),this,SLOT(update()));
	m_locationId = locationid;
	ui.hexEditor->setData(m_data->data());
	ui.locationIdLabel->setText("0x" + QString::number(locationid,16).toUpper());
	//We know that every 20 bytes is a line.
	//int lines = m_data->data().size() / 20;
	//Assume each line is 30 pixels?;
	//this->setMinimumHeight(lines * 35 + 50);
	return true;*/
}
void NitrousSettingsView::update()
{
	//ui.hexEditor->setData(m_data->data());
}

void NitrousSettingsView::loadRamButtonClicked()
{
	/*if (QMessageBox::information(0,"Warning","Doing this will reload the block from ram, and wipe out any changes you may have made. Are you sure you want to do this?",QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
	{
		QLOG_DEBUG() << "Ok";
		m_data->updateFromRam();
		//emit reloadData(m_locationId,true);
	}
	else
	{
		QLOG_DEBUG() << "Not ok";
	}*/

}

void NitrousSettingsView::loadFlashButtonClicked()
{
/*	if (QMessageBox::information(0,"Warning","Doing this will reload the block from flash, and wipe out any changes you may have made. Are you sure you want to do this?",QMessageBox::Yes,QMessageBox::No) == QMessageBox::Yes)
	{
		QLOG_DEBUG() << "Ok";
		//emit reloadData(m_locationId,false);
		m_data->updateFromFlash();
	}
	else
	{
		QLOG_DEBUG() << "Not ok";
	}*/
}

NitrousSettingsView::~NitrousSettingsView()
{
}
void NitrousSettingsView::saveFlashButtonClicked()
{

	unsigned short temp = 0;

	temp = (ui.lowRPMPulseWidthLineEdit->text().toFloat() * 1250);
	qba[82] = (temp >> 8 ) & 0xff;
	qba[83] = temp & 0xff;

	temp = (ui.highRPMPulseWidthLineEdit->text().toFloat() * 1250);
	qba[84] = (temp >> 8 ) & 0xff;
	qba[85] = temp & 0xff;

	temp = (ui.enableRPMLineEdit->text().toInt() * 2);
	qba[86] = (temp >> 8 ) & 0xff;
	qba[87] = temp & 0xff;

	temp = (ui.disableRPMLineEdit->text().toInt() * 2);
	qba[88] = (temp >> 8 ) & 0xff;
	qba[89] = temp & 0xff;

	temp = (ui.enableTPSThresholdLineEdit->text().toInt() * 640);
	qba[90] = (temp >> 8 ) & 0xff;
	qba[91] = temp & 0xff;

	temp = (ui.disableKPAThresholdLineEdit->text().toInt() * 100);
	qba[92] = (temp >> 8 ) & 0xff;
	qba[93] = temp & 0xff;

	m_data->updateValue(qba);

}

void NitrousSettingsView::saveRamButtonClicked()
{
	//emit saveData(m_locationId,ui.hexEditor->data(),0); //0 for RAM, 1 for flash.
}
