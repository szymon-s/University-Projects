/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pl.polsl.Controller;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.ResourceBundle;
import javafx.beans.property.StringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;
import javafx.stage.FileChooser;
import pl.polsl.Model.EmptyFileException;
import pl.polsl.Model.Model;
import pl.polsl.View.View;

/**
 * FXML Controller class which connects Model and View.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public class Controller implements Initializable {

    /**
     * Model which stores data for sort visualization and implements sort
     * algorithms.
     */
    private Model model = new Model();

    /**
     * View which shows data to the user via UI.
     */
    private View view = new View();

    /**
     * Button which provides opening of FileChooser..
     */
    @FXML
    private Button selectFileButton;
    /**
     * Button which provides start of sort visualization.
     */
    @FXML
    private Button sortButton;

    /**
     * ComboBox with sort algorithms to be selected.
     */
    @FXML
    private ComboBox<?> algorithmsComboBox;

    /**
     * Button which provides loading data from file.
     */
    @FXML
    private Button loadDataButton;

    /**
     * FileChooser which provides Dialog Window for selecting txt file.
     */
    private FileChooser fileChooser;

    /**
     * TextArea which provides communication with user.
     */
    @FXML
    private TextArea messageTextArea;

    /**
     * TableView where sort visualisation is presented to the user.
     */
    @FXML
    private TableView<List<StringProperty>> sortStepsTable;

    /**
     * Initializes the controller class.
     *
     * @param url.
     * @param rb.
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        List<String> list = new ArrayList<>(Arrays.asList("BubbleSort", "QuickSort", "SelectionSort", "InsertionSort"));
        ObservableList arguments = FXCollections.observableList(list);
        algorithmsComboBox.setItems(arguments);
    }

    /**
     * Method which is called after pressing selectFileButton, it opens new
     * dialog window where user can select file with data.
     *
     * @param event.
     */
    @FXML
    private void openFileChooser(ActionEvent event) {
        fileChooser = new FileChooser();
        fileChooser.setTitle("Choose File");
        fileChooser.getExtensionFilters().addAll(
                new FileChooser.ExtensionFilter("Text Files", "*.txt"));
        File selectedFile = fileChooser.showOpenDialog(selectFileButton.getScene().getWindow());
        setModelsFile(selectedFile);
        if (selectedFile != null) {
            showMessage("File " + selectedFile.getName() + " loaded successfully!", messageTextArea);
        } else {
            showMessage("File loading failure! Try again...", messageTextArea);
        }
    }

    /**
     * Metod which is called after pressing sortButton, it starts choosen sort
     * algorithm and displays it's results to the user via TableView.
     *
     * @param event.
     */
    @FXML
    private void sortData(ActionEvent event) {
        if (algorithmsComboBox.getValue() != null) {
            setModelsSortName(algorithmsComboBox.getValue().toString());
            if (getModelsData() == null || getModelsData().isEmpty()) {
                showMessage("There is no data loaded! Try again...", messageTextArea);
            } else {
                List<Double> data = new ArrayList<>(getModelsData());
                sortData(data, getSortedData());
                sortStepsTable.getItems().clear();
                showSortResults(getSortedData(), sortStepsTable);
                showMessage(getModelsSortName() + " ended successfully!", messageTextArea);
                getSortedData().clear();

            }
        } else {
            showMessage("There is no sort algorithm selected! Try again...", messageTextArea);
        }
    }

    /**
     * Method which is called after pressing loadDataButton, it loads data from
     * file to the Model and sets TableView columns names.
     *
     * @param event.
     */
    @FXML
    private void loadDataFromFile(ActionEvent event) {
        File file = getModelsFile();
        sortStepsTable.getColumns().clear();
        sortStepsTable.getItems().clear();
        if (file != null) {
            showMessage(setModelsData(), messageTextArea);
        } else {
            getModelsData().clear();
            showMessage("No file loaded. Try again...", messageTextArea);
        }
    }

    /**
     * Print sort steps to the TableView.
     *
     * @param dataSorted data to be printed.
     * @param table TableView which shows data to the user.
     */
    private void showSortResults(List<List<Double>> dataSorted, TableView table) {
        this.view.printSortResults(dataSorted, table);
    }

    /**
     * Set file tp the model.
     *
     * @param file with data to be sorted.
     */
    private void setModelsFile(File file) {
        this.model.setFile(file);
    }

    /**
     * Get sortName from Model.
     *
     * @return name of sort algorithm.
     */
    private String getModelsSortName() {
        return this.model.getSortName();
    }

    /**
     * Set sortName to the model.
     *
     * @param sortName name of sort algorithm.
     */
    private void setModelsSortName(String sortName) {
        this.model.setSortName(sortName);
    }

    /**
     * Get file from Model.
     *
     * @return File selected by user which is stored in Model.
     */
    private File getModelsFile() {
        return this.model.getFile();
    }

    /**
     * Set data to the model and handling exceptions thrown by Model's loadData
     * method.
     *
     * @return message which will be shown to the user.
     */
    private String setModelsData() {
        try {
            loadModelsData();
            List<Double> temporaryData = new ArrayList<>(getModelsData());
            showTableColumns(temporaryData, sortStepsTable);
            return "Data loaded successfully!";

        } catch (IOException e) {
            showMessage("Exception during opening the file. Try again...", messageTextArea);
            return "Data loading failed! Try again...";
        } catch (EmptyFileException e) {
            showMessage(e.getMessage(), messageTextArea);
            return "Data loading failed! Try again...";
        }
    }

    /**
     * Print columns of the TableView.
     *
     * @param data original data to be shown as columns names.
     * @param table TableView where sorting steps will be shown.
     */
    private void showTableColumns(List<Double> data, TableView table) {
        this.view.printTableColumns(data, table);
    }

    /**
     * Load data from file to Model.
     *
     * @throws IOException if there is no file.
     * @throws EmptyFileException if file has invalid data.
     */
    private void loadModelsData() throws IOException, EmptyFileException {
        this.model.loadData();
    }

    /**
     * Get data from the Model.
     *
     * @return List of Double values.
     */
    private List<Double> getModelsData() {
        return this.model.getData();
    }

    /**
     * Get List with sort steps.
     *
     * @return List of Lists of Double values which stores all sorting steps.
     */
    private List<List<Double>> getSortedData() {
        return this.model.getSortingSteps();
    }

    /**
     * Print message to the message TextArea.
     *
     * @param message to be displayed
     * @param textArea where data will be displayed.
     */
    private void showMessage(String message, TextArea textArea) {
        this.view.printMessage(message, textArea);
    }

    /**
     * Use SortAlgorithm stored in Model to sort the data.
     *
     * @param data List of Double values with data to be sorted.
     * @param sortedData List of Lists of Double values which stores sort steps.
     */
    private void sortData(List<Double> data, List<List<Double>> sortedData) {
        this.model.getSortAlgorithm().sort(data, sortedData);
    }

}
