package pl.polsl.Model;

import java.util.ArrayList;
import java.util.List;

/**
 * Class which implements SortAlgorithm interface, it's used to do the Bubble
 * Sort algorithm.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public class BubbleSort implements SortAlgorithm {

    /**
     * Method which sort List using Bubble Sort algorithm.
     *
     * @param data List of Double values with data to be sorted.
     * @param sortedData List of Lists of Double values which stores ale steps
     * done by sort algorithm.
     */
    @Override
    public void sort(List<Double> data, List<List<Double>> sortedData) {
        for (int i = 0; i < data.size() - 1; i++) {
            for (int j = 0; j < data.size() - i - 1; j++) {
                if (data.get(j) > data.get(j + 1)) {
                    Double temp = data.get(j);
                    data.set(j, data.get(j + 1));
                    data.set(j + 1, temp);
                    sortedData.add(new ArrayList<>(data));
                }
            }
        }
    }
}
