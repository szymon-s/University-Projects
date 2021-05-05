package pl.polsl.Model;

import java.io.File;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

/**
 * Model class used to store the data which are used by the View.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public class Model {

    /**
     * File object which contains data to be sorted.
     */
    private File file;

    /**
     * List of Double values which stores data to be sorted and then printed to
     * the console.
     */
    private List<Double> data;

    /**
     * List of Lists of Double values which stores all values created during
     * sorting.
     */
    private List<List<Double>> sortingSteps = new ArrayList<>();

    /**
     * String which stores name of the sort algorithm.
     */
    private String sortName;

    /**
     * Implementation of the interface SortAlgorithm.
     */
    private SortAlgorithm sortAlgorithm;

    /**
     * Default Model constructor.
     */
    public Model() {
    }

    ;
    
    /**
     * Model constructor which sets file, sortName, sortAlgorithm and creates
     * sortingSteps List.
     * @param fileName String which stores name of the file with the data.
     * @param sortName String which stores name of the sort algorithm.
     */
    public Model(String fileName, String sortName) {
        switch (sortName) {
            case "QuickSort":
                this.sortAlgorithm = new QuickSort();
                break;
            case "BubbleSort":
                this.sortAlgorithm = new BubbleSort();
                break;
            case "InsertionSort":
                this.sortAlgorithm = new InsertionSort();
                break;
            case "SelectionSort":
                this.sortAlgorithm = new SelectionSort();
                break;
        }
        this.sortName = sortName;
        file = new File(fileName);
        sortingSteps = new ArrayList<>();
    }

    /**
     * Set file which contains data to be sorted.
     *
     * @param file File with data.
     */
    public void setFile(File file) {
        this.file = file;
    }

    /**
     * Get file which contains data to be sorted.
     *
     * @return file.
     */
    public File getFile() {
        return this.file;
    }

    /**
     * Set Sort name and create implementation of sortAlgorithm interface.
     *
     * @param sortName name of sort algorithm.
     */
    public void setSortName(String sortName) {

        switch (sortName) {
            case "QuickSort":
                this.sortAlgorithm = new QuickSort();
                this.sortName = sortName;
                break;
            case "BubbleSort":
                this.sortAlgorithm = new BubbleSort();
                this.sortName = sortName;
                break;
            case "InsertionSort":
                this.sortAlgorithm = new InsertionSort();
                this.sortName = sortName;
                break;
            case "SelectionSort":
                this.sortAlgorithm = new SelectionSort();
                this.sortName = sortName;
                break;
        }
    }

    /**
     * Get sort algortihm name which is used in the program.
     *
     * @return String value with name of the sort algorithm.
     */
    public String getSortName() {
        return this.sortName;
    }

    /**
     * Set data which store ArrayList of double values.
     *
     * @param data List of Double values which has to be stored in the Model
     */
    public void setData(ArrayList<Double> data) {
        this.data = data;
    }

    /**
     * Get List of Double values stored in the model.
     *
     * @return List of Double values.
     */
    public List<Double> getData() {
        return this.data;
    }

    /**
     * Get List of Lits of Double values which store result of sorting.
     *
     * @return sortingSteps with data created duting sorting.
     */
    public List<List<Double>> getSortingSteps() {
        return this.sortingSteps;
    }

    /**
     * Method which loads the data from the text file to the Model's data.
     *
     * @throws java.io.IOException when there is problem during opening the file
     * @throws pl.polsl.Model.EmptyFileException when there is no file, file is empty 
     * or the data in it is incorrect
     */
    public void loadData() throws IOException, EmptyFileException {

        if (file == null) {
            data = null;
            throw new EmptyFileException("There is no file loaded. Try again...");
        }
        data = new ArrayList<>();
        Scanner input = new Scanner(file,
                StandardCharsets.UTF_8);
        while (input.hasNextDouble()) {
            double value = input.nextDouble();
            data.add(value);
        }
        if (data.isEmpty()) {
            data = null;
            throw new EmptyFileException("Empty file, or incorrect data. Try again...");
        }
    }

    /**
     * Get SortAlgorithm which is used in the program.
     *
     * @return sortAlgorithm which is instance of class SortAlgorithm
     */
    public SortAlgorithm getSortAlgorithm() {
        return sortAlgorithm;
    }
}
