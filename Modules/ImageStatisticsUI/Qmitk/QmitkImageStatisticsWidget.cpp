/*===================================================================

The Medical Imaging Interaction Toolkit (MITK)

Copyright (c) German Cancer Research Center,
Division of Medical and Biological Informatics.
All rights reserved.

This software is distributed WITHOUT ANY WARRANTY; without
even the implied warranty of MERCHANTABILITY or FITNESS FOR
A PARTICULAR PURPOSE.

See LICENSE.txt or http://www.mitk.org for details.

===================================================================*/

#include "QmitkImageStatisticsWidget.h"

#include "QmitkTableModelToStringConverter.h"

#include <QSortFilterProxyModel>
#include <QClipboard>

QmitkImageStatisticsWidget::QmitkImageStatisticsWidget(QWidget* parent) : QWidget(parent)
{
  m_Controls.setupUi(this);
  m_imageStatisticsModel = new QmitkImageStatisticsTableModel(parent);
  //temporarily disabled because 4D clipboard functionality is not implemented yet
  m_Controls.checkBox4dCompleteTable->setVisible(false);
  CreateConnections();
  m_ProxyModel = new QSortFilterProxyModel(this);
  m_Controls.tableViewStatistics->setModel(m_ProxyModel);
  m_ProxyModel->setSourceModel(m_imageStatisticsModel);
}

void QmitkImageStatisticsWidget::SetDataStorage(mitk::DataStorage* newDataStorage)
{
  m_imageStatisticsModel->SetDataStorage(newDataStorage);
  m_Controls.tableViewStatistics->resizeColumnsToContents(); // should call data in table model
  m_Controls.tableViewStatistics->resizeRowsToContents();
}

void QmitkImageStatisticsWidget::SetImageNodes(const std::vector<mitk::DataNode::ConstPointer>& nodes)
{
  m_imageStatisticsModel->SetImageNodes(nodes);
}

void QmitkImageStatisticsWidget::SetMaskNodes(const std::vector<mitk::DataNode::ConstPointer>& nodes)
{
  m_imageStatisticsModel->SetMaskNodes(nodes);
}

void QmitkImageStatisticsWidget::Reset()
{
  m_imageStatisticsModel->Clear();
}

void QmitkImageStatisticsWidget::CreateConnections()
{
	connect(m_Controls.buttonCopyImageStatisticsToClipboard, &QPushButton::clicked, this, &QmitkImageStatisticsWidget::OnClipboardButtonClicked);
}

void QmitkImageStatisticsWidget::OnClipboardButtonClicked()
{
  QmitkTableModelToStringConverter converter;
  converter.SetTableModel(m_imageStatisticsModel);
  converter.SetIncludeHeaderData(true);
  converter.SetColumnDelimiter('\t');

  QString clipboardAsString = converter.GetString();
  QApplication::clipboard()->setText(clipboardAsString, QClipboard::Clipboard);
}
