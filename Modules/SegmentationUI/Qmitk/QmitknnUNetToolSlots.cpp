#include "QmitknnUNetToolGUI.h"
#include <QDir>
#include <QDirIterator>
#include <QMessageBox>
#include <algorithm>

void QmitknnUNetToolGUI::EnableWidgets(bool enabled)
{
  Superclass::EnableWidgets(enabled);
  m_Controls.previewButton->setEnabled(false);
}

void QmitknnUNetToolGUI::ClearAllComboBoxes()
{
  m_Controls.modelBox->clear();
  m_Controls.taskBox->clear();
  m_Controls.foldBox->clear();
  m_Controls.trainerBox->clear();
}

template <typename T>
T QmitknnUNetToolGUI::FetchFoldersFromDir(const QString &path)
{
  T folders;
  for (QDirIterator it(path, QDir::AllDirs, QDirIterator::NoIteratorFlags); it.hasNext();)
  {
    it.next();
    if (!it.fileName().startsWith('.'))
    {
      folders.push_back(it.fileName());
    }
  }
  return folders;
}

void QmitknnUNetToolGUI::OnDirectoryChanged(const QString &resultsFolder)
{
  m_Controls.previewButton->setEnabled(false);
  this->ClearAllComboBoxes();
  m_ModelDirectory = resultsFolder + QDir::separator() + "nnUNet";
  auto models = FetchFoldersFromDir<QStringList>(m_ModelDirectory);
  QStringList validlist; // valid list of models supported by nnUNet
  validlist << "2d"
            << "3d_lowres"
            << "3d_fullres"
            << "3d_cascade_fullres"
            << "ensembles";
  std::for_each(models.begin(),
                models.end(),
                [this, validlist](QString model)
                {
                  if (validlist.contains(model, Qt::CaseInsensitive))
                    m_Controls.modelBox->addItem(model);
                });
}

void QmitknnUNetToolGUI::OnModelChanged(const QString &text)
{
  QString updatedPath(QDir::cleanPath(m_ModelDirectory + QDir::separator() + text));
  m_Controls.taskBox->clear();
  auto datasets = FetchFoldersFromDir<QStringList>(updatedPath);
  std::for_each(datasets.begin(), datasets.end(), [this](QString dataset) { m_Controls.taskBox->addItem(dataset); });
}

void QmitknnUNetToolGUI::OnTaskChanged(const QString &text)
{
  QString updatedPath = QDir::cleanPath(m_ModelDirectory + QDir::separator() + m_Controls.modelBox->currentText() +
                                        QDir::separator() + text);
  m_Controls.trainerBox->clear();
  m_Controls.plannerBox->clear();
  auto trainerPlanners = FetchFoldersFromDir<QStringList>(updatedPath);
  QStringList trainers, planners;
  foreach (QString trainerPlanner, trainerPlanners)
  {
    trainers << trainerPlanner.split("__", QString::SplitBehavior::SkipEmptyParts).first();
    planners << trainerPlanner.split("__", QString::SplitBehavior::SkipEmptyParts).last();
  }
  trainers.removeDuplicates();
  planners.removeDuplicates();
  std::for_each(trainers.begin(), trainers.end(), [this](QString trainer) { m_Controls.trainerBox->addItem(trainer); });
  std::for_each(planners.begin(), planners.end(), [this](QString planner) { m_Controls.plannerBox->addItem(planner); });
}

void QmitknnUNetToolGUI::OnTrainerChanged(const QString &trainerSelected)
{
  m_Controls.foldBox->clear();
  if (m_Controls.modelBox->currentText() != "ensembles")
  {
    QString updatedPath(QDir::cleanPath(m_ModelDirectory + QDir::separator() + m_Controls.modelBox->currentText() +
                                        QDir::separator() + m_Controls.taskBox->currentText() + QDir::separator() +
                                        m_Controls.trainerBox->currentText() + "__" + trainerSelected));
    auto folds = FetchFoldersFromDir<QStringList>(updatedPath);
    std::for_each(folds.begin(),
                  folds.end(),
                  [this](QString fold)
                  {
                    if (fold.startsWith("fold_", Qt::CaseInsensitive)) // imposed by nnUNet
                      m_Controls.foldBox->addItem(fold);
                  });
    if (m_Controls.foldBox->count() != 0)
    {
      m_Controls.previewButton->setEnabled(true);
    }
  }
  else
  {
    m_Controls.previewButton->setEnabled(true);
  }
}

void QmitknnUNetToolGUI::OnPythonPathChanged(const QString &pyEnv)
{
  if (pyEnv == QString("Select"))
  {
    QString path =
      QFileDialog::getExistingDirectory(m_Controls.pythonEnvComboBox->parentWidget(), "Python Path", "dir");
    if (!path.isEmpty())
    {
      m_Controls.pythonEnvComboBox->insertItem(0, path);
      m_Controls.pythonEnvComboBox->setCurrentIndex(0);
    }
  }
  else if (!IsNNUNetInstalled(pyEnv))
  {
    std::string warning =
      "WARNING: nnUNet is not detected on the Python environment you selected. Please select another "
      "environment or create one. For more info refer https://github.com/MIC-DKFZ/nnUNet";
    ShowErrorMessage(warning);
  }
}

void QmitknnUNetToolGUI::OnCheckBoxChanged(int state)
{
  bool visibility = false;
  if (state == Qt::Checked)
  {
    visibility = true;
  }
  ctkCheckBox *box = qobject_cast<ctkCheckBox *>(sender());
  if (box != nullptr)
  {
    if (box->objectName() == QString("nopipBox"))
    {
      m_Controls.codedirectoryBox->setVisible(visibility);
      m_Controls.nnUnetdirLabel->setVisible(visibility);
    }
    else if (box->objectName() == QString("multiModalBox"))
    {
      m_Controls.multiModalSpinLabel->setVisible(visibility);
      m_Controls.multiModalSpinBox->setVisible(visibility);
      m_Controls.posSpinBoxLabel->setVisible(visibility);
      m_Controls.posSpinBox->setVisible(visibility);
      if (visibility)
      {
        QmitkDataStorageComboBox *defaultImage = new QmitkDataStorageComboBox(this, true);
        defaultImage->setObjectName(QString("multiModal_" + QString::number(0)));
        mitk::nnUNetTool::Pointer tool = this->GetConnectedToolAs<mitk::nnUNetTool>();
        defaultImage->SetDataStorage(tool->GetDataStorage());
        defaultImage->SetSelectedNode(tool->GetDataStorage()->GetNode());
        defaultImage->setDisabled(true);
        m_Controls.advancedSettingsLayout->addWidget(defaultImage, this->m_UI_ROWS + m_Modalities.size() + 1, 1, 1, 3);
        m_Modalities.push_back(defaultImage);
        m_Controls.posSpinBox->setMaximum(this->m_Modalities.size() - 1);
        m_UI_ROWS++;
      }
      else
      {
        OnModalitiesNumberChanged(0);
        m_Controls.multiModalSpinBox->setValue(0);
        m_Controls.posSpinBox->setMaximum(0);
      }
    }
  }
}

void QmitknnUNetToolGUI::OnModalitiesNumberChanged(int num)
{
  while (num > static_cast<int>(this->m_Modalities.size()-1))
  {
    QmitkDataStorageComboBox *multiModalBox = new QmitkDataStorageComboBox(this, true);
    mitk::nnUNetTool::Pointer tool = this->GetConnectedToolAs<mitk::nnUNetTool>();
    multiModalBox->SetDataStorage(tool->GetDataStorage());
    multiModalBox->SetPredicate(this->m_MultiModalPredicate);
    multiModalBox->setObjectName(QString("multiModal_" + QString::number(m_Modalities.size() + 1)));
    m_Controls.advancedSettingsLayout->addWidget(multiModalBox, this->m_UI_ROWS + m_Modalities.size() + 1, 1, 1, 3);
    m_Modalities.push_back(multiModalBox);
  }
  while (num < static_cast<int>(this->m_Modalities.size()-1) && !m_Modalities.empty())
  {
    QmitkDataStorageComboBox *child = m_Modalities.back();
    if (child->objectName() == "multiModal_0")
    {
      std::iter_swap(this->m_Modalities.end() - 2, this->m_Modalities.end()-1);
      child = m_Modalities.back();
    }
    delete child; // delete the layout item
    m_Modalities.pop_back();
  }
  m_Controls.posSpinBox->setMaximum(this->m_Modalities.size()-1);
  m_Controls.advancedSettingsLayout->update();
}


void QmitknnUNetToolGUI::OnModalPositionChanged(int posIdx)
{
  if (posIdx < static_cast<int>(this->m_Modalities.size()))
  {
    int currPos = 0;
    bool stopCheck = false;
    // for-loop clears all widgets from the QGridLayout and also, finds the position of loaded-image widget.
    for (QmitkDataStorageComboBox *multiModalBox : this->m_Modalities) 
    {
      m_Controls.advancedSettingsLayout->removeWidget(multiModalBox);
      multiModalBox->setParent(nullptr);
      if (multiModalBox->objectName() != "multiModal_0" && !stopCheck)
      {
        currPos++;
      }
      else
      {
        stopCheck = true;
      }
    }
    // moving the loaded-image widget to the required position
    std::iter_swap(this->m_Modalities.begin() + currPos, this->m_Modalities.begin() + posIdx); 
    // re-adding all widgets in the order
    for (int i = 0; i < static_cast<int>(this->m_Modalities.size()); ++i)
    {
      QmitkDataStorageComboBox *multiModalBox = this->m_Modalities[i];
      m_Controls.advancedSettingsLayout->addWidget(multiModalBox, this->m_UI_ROWS + i + 1, 1, 1, 3);
    }
    m_Controls.advancedSettingsLayout->update();
  }
}

void QmitknnUNetToolGUI::AutoParsePythonPaths()
{
  QString homeDir = QDir::homePath();
  std::vector<QString> searchDirs;
#ifdef _WIN32
  searchDirs.push_back(QString("C:") + QDir::separator() + QString("ProgramData") + QDir::separator() +
                       QString("anaconda3"));
#else
  // Add search locations for possible standard python paths here
  searchDirs.push_back(homeDir + QDir::separator() + "environments");
  searchDirs.push_back(homeDir + QDir::separator() + "anaconda3");
  searchDirs.push_back(homeDir + QDir::separator() + "miniconda3");
  searchDirs.push_back(homeDir + QDir::separator() + "opt" + QDir::separator() + "miniconda3");
  searchDirs.push_back(homeDir + QDir::separator() + "opt" + QDir::separator() + "anaconda3");
#endif
  for (QString searchDir : searchDirs)
  {
    if (searchDir.endsWith("anaconda3", Qt::CaseInsensitive))
    {
      if (QDir(searchDir).exists())
      {
        m_Controls.pythonEnvComboBox->insertItem(0, "(base): " + searchDir);
        searchDir.append((QDir::separator() + QString("envs")));
      }
    }
    for (QDirIterator subIt(searchDir, QDir::AllDirs, QDirIterator::NoIteratorFlags); subIt.hasNext();)
    {
      subIt.next();
      QString envName = subIt.fileName();
      if (!envName.startsWith('.')) // Filter out irrelevent hidden folders, if any.
      {
        m_Controls.pythonEnvComboBox->insertItem(0, "(" + envName + "): " + subIt.filePath());
      }
    }
  }
  m_Controls.pythonEnvComboBox->setCurrentIndex(-1);
}

std::vector<std::string> QmitknnUNetToolGUI::FetchSelectedFoldsFromUI()
{
  std::vector<std::string> folds;
  if (!(m_Controls.foldBox->allChecked() || m_Controls.foldBox->noneChecked()))
  {
    QModelIndexList foldList = m_Controls.foldBox->checkedIndexes();
    foreach (QModelIndex index, foldList)
    {
      QString foldQString =
        m_Controls.foldBox->itemText(index.row()).split("_", QString::SplitBehavior::SkipEmptyParts).last();
      folds.push_back(foldQString.toStdString());
    }
  }
  return folds;
}

mitk::ModelParams QmitknnUNetToolGUI::MapToRequest(const QString &modelName,
                                                   const QString &taskName,
                                                   const QString &trainer,
                                                   const QString &planId,
                                                   const std::vector<std::string> &folds)
{
  mitk::ModelParams requestObject;
  requestObject.model = modelName.toStdString();
  requestObject.trainer = trainer.toStdString();
  requestObject.planId = planId.toStdString();
  requestObject.task = taskName.toStdString();
  requestObject.folds = folds;
  return requestObject;
}

void QmitknnUNetToolGUI::SegmentationProcessFailed()
{
  m_Controls.statusLabel->setText(
    "<b>STATUS: </b><i>Error in the segmentation process. No resulting segmentation can be loaded.</i>");
  this->setCursor(Qt::ArrowCursor);
  std::stringstream stream;
  stream << "Error in the segmentation process. No resulting segmentation can be loaded.";
  QMessageBox *messageBox = new QMessageBox(QMessageBox::Critical, nullptr, stream.str().c_str());
  messageBox->exec();
  delete messageBox;
  MITK_ERROR << stream.str();
}

void QmitknnUNetToolGUI::SegmentationResultHandler(mitk::nnUNetTool *tool)
{
  MITK_INFO << "Finished slot";
  tool->RenderOutputBuffer();
  this->SetLabelSetPreview(tool->GetMLPreview());
  tool->IsTimePointChangeAwareOn();
  m_Controls.statusLabel->setText("<b>STATUS: </b><i>Segmentation task finished successfully.</i>");
}
