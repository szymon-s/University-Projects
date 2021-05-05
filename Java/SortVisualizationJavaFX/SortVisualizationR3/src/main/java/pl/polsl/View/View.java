package pl.polsl.View;

import java.util.ArrayList;
import java.util.List;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextArea;

/**
 * View class used to display data to the user via UI.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public class View {

    /**
     * Print columns of the TableView.
     *
     * @param data original data to be shown as columns names.
     * @param table TableView where sorting steps will be shown.
     */
    public void printTableColumns(List<Double> data, TableView<List<StringProperty>> table) {
        int i = 0;
        for (Double element : data) {
            final int index = i;
            TableColumn<List<StringProperty>, String> column = new TableColumn<>(element.toString());
            column.setCellValueFactory(data1 -> data1.getValue().get(index));
            column.setMaxWidth(80.0);
            column.setMinWidth(80.0);
            column.setStyle("-fx-alignment: CENTER;");
            table.getColumns().add(column);
            i++;
        }
    }

    /**
     * Print sort steps to the TableView.
     *
     * @param dataSorted sort steps to be shown.
     * @param table TableView where sorting steps will be shown.
     */
    public void printSortResults(List<List<Double>> dataSorted, TableView<List<StringProperty>> table) {

        ObservableList<List<StringProperty>> stringData = FXCollections.observableArrayList();
        dataSorted.stream().map(array -> {
            List<StringProperty> row = new ArrayList<>();
            array.forEach(element -> {
                row.add(new SimpleStringProperty(element.toString()));
            });
            return row;
        }).forEachOrdered(row -> {
            stringData.add(row);
        });
        table.setFixedCellSize(30.0);
        table.setItems(stringData);
    }

    /**
     * Print message to the message TextArea.
     *
     * @param message to be displayed
     * @param textArea where data will be displayed.
     */
    public void printMessage(String message, TextArea textArea) {
        textArea.setText(message);
    }
}
