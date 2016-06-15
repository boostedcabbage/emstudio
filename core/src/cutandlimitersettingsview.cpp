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

#include "cutandlimitersettingsview.h"
#include "QsLog.h"

CutAndLimiterSettingsView::CutAndLimiterSettingsView(bool isram, bool isflash,QWidget *parent)
{
	Q_UNUSED(parent)
	m_data = 0;
	ui.setupUi(this);
	/*connect(ui.saveFlashPushButton,SIGNAL(clicked()),this,SLOT(saveFlashButtonClicked()));
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
void CutAndLimiterSettingsView::passDatalog(QVariantMap data)
{
	Q_UNUSED(data)
}
bool CutAndLimiterSettingsView::setData(unsigned short locationid,DataBlock *data)
{

	unsigned short temp = 0;
	m_data = (RawData*)(data);
	QByteArray qba = m_data->data();
	unsigned char *tdata = (unsigned char *)qba.data();

	temp = (((tdata[0] << 8) + tdata[1]) / 2);
	ui.injectionRPMDisableLineEdit->setText(QString::number(temp));

	temp = (((tdata[2] << 8) + tdata[3]) / 2);
	ui.injectionRPMEnableLineEdit->setText(QString::number(temp));

	temp = (((tdata[4] << 8) + tdata[5]) / 2);
	ui.ignitionRPMDisableLineEdit->setText(QString::number(temp));

	temp = (((tdata[6] << 8) + tdata[7]) / 2);
	ui.ignitionRPMEnableLineEdit->setText(QString::number(temp));

	temp = (((tdata[8] << 8) + tdata[9]) / 100);
	ui.boostCutDisableLineEdit->setText(QString::number(temp));

	temp = (((tdata[10] << 8) + tdata[11]) / 100);
	ui.boostCutEnableLineEdit->setText(QString::number(temp));

	temp = (((tdata[12] << 8) + tdata[13]) / 2);
	ui.twoStepRPMDisableLineEdit->setText(QString::number(temp));

	temp = (((tdata[14] << 8) + tdata[15]) / 2);
	ui.twoStepRPMEnableLineEdit->setText(QString::number(temp));

	temp = (((tdata[16] << 8) + tdata[17]) / 2);
	ui.twoStepRetardRPMThresholdLineEdit->setText(QString::number(temp));

	temp = (((tdata[18] << 8) + tdata[19]) / 1024);
	ui.twoStepIgnitionTimingLineEdit->setText(QString::number(temp));



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
void CutAndLimiterSettingsView::update()
{
	//ui.hexEditor->setData(m_data->data());
}

void CutAndLimiterSettingsView::loadRamButtonClicked()
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

void CutAndLimiterSettingsView::loadFlashButtonClicked()
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

CutAndLimiterSettingsView::~CutAndLimiterSettingsView()
{
}
void CutAndLimiterSettingsView::saveFlashButtonClicked()
{
	unsigned short temp = 0;

	temp = (ui.injectionRPMDisableLineEdit->text().toInt() * 2);
	qba[0] = (temp >> 8 ) & 0xff;
	qba[1] = temp & 0xff;

	temp = (ui.injectionRPMEnableLineEdit->text().toInt() * 2);
	qba[2] = (temp >> 8 ) & 0xff;
	qba[3] = temp & 0xff;

	temp = (ui.ignitionRPMDisableLineEdit->text().toInt() * 2);
	qba[4] = (temp >> 8 ) & 0xff;
	qba[5] = temp & 0xff;

	temp = (ui.ignitionRPMEnableLineEdit->text().toInt() * 2);
	qba[6] = (temp >> 8 ) & 0xff;
	qba[7] = temp & 0xff;

	temp = (ui.boostCutDisableLineEdit->text().toInt() * 100);
	qba[8] = (temp >> 8 ) & 0xff;
	qba[9] = temp & 0xff;

	temp = (ui.boostCutEnableLineEdit->text().toInt() * 100);
	qba[10] = (temp >> 8 ) & 0xff;
	qba[11] = temp & 0xff;

	temp = (ui.twoStepRPMDisableLineEdit->text().toInt() * 2);
	qba[12] = (temp >> 8 ) & 0xff;
	qba[13] = temp & 0xff;

	temp = (ui.twoStepRPMEnableLineEdit->text().toInt() * 2);
	qba[14] = (temp >> 8 ) & 0xff;
	qba[15] = temp & 0xff;

	temp = (ui.twoStepRetardRPMThresholdLineEdit->text().toInt() * 2);
	qba[16] = (temp >> 8 ) & 0xff;
	qba[17] = temp & 0xff;

	temp = (ui.twoStepIgnitionTimingLineEdit->text().toInt() * 1024);
	qba[18] = (temp >> 8 ) & 0xff;
	qba[19] = temp & 0xff;


	m_data->updateValue(qba);
}

void CutAndLimiterSettingsView::saveRamButtonClicked()
{
	//emit saveData(m_locationId,ui.hexEditor->data(),0); //0 for RAM, 1 for flash.
}
