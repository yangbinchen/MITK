file(GLOB_RECURSE H_FILES RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/include/*")

set(CPP_FILES
  QmitkAbstractDataStorageModel.cpp
  QmitkAbstractMultiWidget.cpp
  QmitkAbstractNodeSelectionWidget.cpp
  QmitkApplicationCursor.cpp
  QmitkDataStorageComboBox.cpp
  QmitkDataStorageDefaultListModel.cpp
  QmitkDataStorageHistoryModel.cpp
  QmitkDataStorageListModel.cpp
  QmitkDataStorageTableModel.cpp
  QmitkDataStorageSimpleTreeModel.cpp
  QmitkDataStorageTreeModel.cpp
  QmitkDataStorageTreeModelInternalItem.cpp
  QmitkDnDDataNodeWidget.cpp
  QmitkFileReaderOptionsDialog.cpp
  QmitkFileReaderWriterOptionsWidget.cpp
  QmitkFileWriterOptionsDialog.cpp
  QmitkInteractionSchemeToolBar.cpp
  QmitkIOUtil.cpp
  QmitkLevelWindowPresetDefinitionDialog.cpp
  QmitkLevelWindowRangeChangeDialog.cpp
  QmitkLevelWindowWidgetContextMenu.cpp
  QmitkLevelWindowWidget.cpp
  QmitkLineEditLevelWindowWidget.cpp
  QmitkMemoryUsageIndicatorView.cpp
  QmitkMimeTypes.cpp
  QmitkMultiNodeSelectionWidget.cpp
  QmitkMultiWidgetConfigurationToolBar.cpp
  QmitkMultiWidgetLayoutManager.cpp
  QmitkMultiWidgetLayoutSelectionWidget.cpp
  QmitkNodeDescriptor.cpp
  QmitkNodeSelectionButton.cpp
  QmitkNodeSelectionConstants.cpp
  QmitkNodeSelectionDialog.cpp
  QmitkNodeSelectionListItemWidget.cpp
  QmitkNodeSelectionPreferenceHelper.cpp
  QmitkNodeDescriptor.cpp
  QmitkColoredNodeDescriptor.cpp
  QmitkNodeDescriptorManager.cpp
  QmitkProgressBar.cpp
  QmitkPropertiesTableEditor.cpp
  QmitkPropertiesTableModel.cpp
  QmitkPropertyDelegate.cpp
  QmitkRegisterClasses.cpp
  QmitkRenderingManager.cpp
  QmitkRenderWindowDataStorageTreeModel.cpp
  QmitkRenderingManagerFactory.cpp
  QmitkRenderWindow.cpp
  QmitkRenderWindowMenu.cpp
  QmitkRenderWindowUtilityWidget.cpp
  QmitkRenderWindowWidget.cpp
  QmitkRenderWindowContextDataStorageInspector.cpp
  mitkRenderWindowLayerController.cpp
  mitkRenderWindowLayerUtilities.cpp
  mitkRenderWindowViewDirectionController.cpp
  QmitkServiceListWidget.cpp
  QmitkSingleNodeSelectionWidget.cpp
  QmitkSliceNavigationWidget.cpp
  QmitkSliderLevelWindowWidget.cpp
  QmitkStdMultiWidget.cpp
  QmitkStepperAdapter.cpp
  QmitkMxNMultiWidget.cpp
  QmitkDataStorageComboBoxWithSelectNone.cpp
  QmitkDataStorageFilterProxyModel.cpp
  QmitkPropertyItem.cpp
  QmitkPropertyItemDelegate.cpp
  QmitkPropertyItemModel.cpp
  QmitkStyleManager.cpp
  QmitkAbstractDataStorageInspector.cpp
  QmitkDataStorageFavoriteNodesInspector.cpp
  QmitkDataStorageListInspector.cpp
  QmitkDataStorageTreeInspector.cpp
  QmitkDataStorageSelectionHistoryInspector.cpp
  QmitkModelViewSelectionConnector.cpp
  mitkIDataStorageInspectorProvider.cpp
  mitkQtWidgetsActivator.cpp
  mitkDataStorageInspectorGenerator.cpp
  QmitkOverlayWidget.cpp
  QmitkSimpleTextOverlayWidget.cpp
  QmitkNodeDetailsDialog.cpp
)

set(MOC_H_FILES
  include/QmitkAbstractDataStorageModel.h
  include/QmitkAbstractMultiWidget.h
  include/QmitkAbstractNodeSelectionWidget.h
  include/QmitkDataStorageComboBox.h
  include/QmitkDataStorageTableModel.h
  include/QmitkDataStorageTreeModel.h
  include/QmitkDataStorageSimpleTreeModel.h
  include/QmitkDataStorageDefaultListModel.h
  include/QmitkDnDDataNodeWidget.h
  include/QmitkFileReaderOptionsDialog.h
  include/QmitkFileReaderWriterOptionsWidget.h
  include/QmitkFileWriterOptionsDialog.h
  include/QmitkInteractionSchemeToolBar.h
  include/QmitkLevelWindowPresetDefinitionDialog.h
  include/QmitkLevelWindowRangeChangeDialog.h
  include/QmitkLevelWindowWidgetContextMenu.h
  include/QmitkLevelWindowWidget.h
  include/QmitkLineEditLevelWindowWidget.h
  include/QmitkMemoryUsageIndicatorView.h
  include/QmitkMultiNodeSelectionWidget.h
  include/QmitkMultiWidgetConfigurationToolBar.h
  include/QmitkMultiWidgetLayoutManager.h
  include/QmitkMultiWidgetLayoutSelectionWidget.h
  include/QmitkNodeDescriptor.h
  include/QmitkNodeSelectionButton.h
  include/QmitkNodeSelectionDialog.h
  include/QmitkNodeSelectionListItemWidget.h
  include/QmitkColoredNodeDescriptor.h
  include/QmitkNodeDescriptorManager.h
  include/QmitkProgressBar.h
  include/QmitkPropertiesTableEditor.h
  include/QmitkPropertyDelegate.h
  include/QmitkRenderingManager.h
  include/QmitkRenderWindow.h
  include/QmitkRenderWindowDataStorageTreeModel.h
  include/QmitkRenderWindowMenu.h
  include/QmitkRenderWindowUtilityWidget.h
  include/QmitkRenderWindowWidget.h
  include/QmitkRenderWindowContextDataStorageInspector.h
  include/mitkRenderWindowLayerController.h
  include/mitkRenderWindowLayerUtilities.h
  include/mitkRenderWindowViewDirectionController.h
  include/QmitkServiceListWidget.h
  include/QmitkSingleNodeSelectionWidget.h
  include/QmitkSliceNavigationWidget.h
  include/QmitkSliderLevelWindowWidget.h
  include/QmitkStdMultiWidget.h
  include/QmitkMxNMultiWidget.h
  include/QmitkStepperAdapter.h
  include/QmitkDataStorageComboBoxWithSelectNone.h
  include/QmitkPropertyItemDelegate.h
  include/QmitkPropertyItemModel.h
  include/QmitkAbstractDataStorageInspector.h
  include/QmitkDataStorageFavoriteNodesInspector.h
  include/QmitkDataStorageListInspector.h
  include/QmitkDataStorageTreeInspector.h
  include/QmitkDataStorageHistoryModel.h
  include/QmitkDataStorageSelectionHistoryInspector.h
  include/QmitkModelViewSelectionConnector.h
  include/QmitkOverlayWidget.h
  include/QmitkSimpleTextOverlayWidget.h
  include/QmitkNodeDetailsDialog.h
)

set(UI_FILES
  src/QmitkFileReaderOptionsDialog.ui
  src/QmitkFileWriterOptionsDialog.ui
  src/QmitkLevelWindowPresetDefinition.ui
  src/QmitkLevelWindowWidget.ui
  src/QmitkLevelWindowRangeChange.ui
  src/QmitkMemoryUsageIndicator.ui
  src/QmitkMultiNodeSelectionWidget.ui
  src/QmitkMultiWidgetLayoutSelectionWidget.ui
  src/QmitkNodeSelectionDialog.ui
  src/QmitkNodeSelectionListItemWidget.ui
  src/QmitkRenderWindowContextDataStorageInspector.ui
  src/QmitkServiceListWidgetControls.ui
  src/QmitkSingleNodeSelectionWidget.ui
  src/QmitkSliceNavigationWidget.ui
  src/QmitkDataStorageListInspector.ui
  src/QmitkDataStorageTreeInspector.ui
  src/QmitkDataStorageSelectionHistoryInspector.ui
)

set(QRC_FILES
  resource/Qmitk.qrc
)
