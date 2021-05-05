package pl.polsl.Model;

import java.util.ArrayList;
import java.util.List;

/**
 * Class which implements SortAlgorithm interface, it's used to do the Selection
 * Sort algorithm.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public class SelectionSort implements SortAlgorithm {

    /**
     * Method which sort List using Selection Sort algorithm.
     *
     * @param data List of Double values with data to be sorted.
     * @param sortedData List of Lists of Double values which stores ale steps
     * done by sort algorithm.
     */
    @Override
    public void sort(List<Double> data, List<List<Double>> sortedData) {
        for (int i = 0; i < data.size() - 1; i++) {
            int min_index = i;
            for (int j = i + 1; j < data.size(); j++) {
                if (data.get(j) < data.get(min_index)) {
                    min_index = j;
                }

            }
            Double temp = data.get(min_index);
            data.set(min_index, data.get(i));
            data.set(i, temp);
            sortedData.add(new ArrayList<>(data));
        }
    }
}
