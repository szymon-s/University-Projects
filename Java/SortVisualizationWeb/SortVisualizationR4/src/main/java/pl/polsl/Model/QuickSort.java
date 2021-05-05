package pl.polsl.Model;

import java.util.ArrayList;
import java.util.List;

/**
 * Class which implements SortAlgorithm interface, it's used to do the Quick
 * Sort algorithm.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public class QuickSort implements SortAlgorithm {

    /**
     * Recursive method which implements Quick Sort algorithm.
     *
     * @param data List od Double values with data to be sorted
     * @param sortedData List of Lists of Double values which stores ale steps
     * done by sort algorithm.
     * @param low Index of first element of collection to be sorted
     * @param high Index of last element of colleciton to be sorted
     */
    private void quickSort(List<Double> data,
            List<List<Double>> sortedData, int low, int high) {

        if (low <= high) {
            int pi = partition(data, sortedData, low, high);
            quickSort(data, sortedData, low, pi - 1);
            quickSort(data, sortedData, pi + 1, high);
        }
    }

    /**
     * Method which puts in order elements of the collection around the key
     * value, key value is always the last element of the sorted collection.
     *
     * @param data List od Double values with data to be sorted
     * @param sortedData List of Lists of Double values which stores ale steps
     * done by sort algorithm.
     * @param low Index of first element of collection to be sorted
     * @param high Index of last element of colleciton to be sorted
     * @return value which modify the indexes in recursive function calls
     */
    private int partition(List<Double> data,
            List<List<Double>> sortedData, int low, int high) {

        Double key = data.get(high);
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (data.get(j) < key) {
                i++;
                Double temp = data.get(i);
                data.set(i, data.get(j));
                data.set(j, temp);
                sortedData.add(new ArrayList<>(data));
            }
        }
        Double temp = data.get(i + 1);
        data.set(i + 1, data.get(high));
        data.set(high, temp);
        return i + 1;
    }

    /**
     * Method which sort List using Quick Sort algorithm.
     *
     * @param data List of Double values with data to be sorted.
     * @param sortedData List of Lists of Double values which stores ale steps
     * done by sort algorithm.
     */
    @Override
    public void sort(List<Double> data, List<List<Double>> sortedData) {
        quickSort(data, sortedData, 0, data.size() - 1);
    }

}
