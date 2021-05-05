package pl.polsl.Model;

import java.util.ArrayList;
import java.util.List;

/**
 * Class which implements SortAlgorithm interface, it's used to do the Insertion
 * Sort algorithm.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public class InsertionSort implements SortAlgorithm {

    /**
     * Method which sort List using Insertion Sort algorithm.
     *
     * @param data List of Double values with data to be sorted.
     * @param sortedData List of Lists of Double values which stores ale steps
     * done by sort algorithm.
     */
    @Override
    public void sort(List<Double> data, List<List<Double>> sortedData) {
        for (int i = 1; i < data.size(); i++) {
            Double key = data.get(i);
            int j = i - 1;
            while ((j >= 0) && (data.get(j) > key)) {
                data.set(j + 1, data.get(j));
                j = j - 1;
            }
            data.set(j + 1, key);
            sortedData.add(new ArrayList<>(data));
        }
    }
}
