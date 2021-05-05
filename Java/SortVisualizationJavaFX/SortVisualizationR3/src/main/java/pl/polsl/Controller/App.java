package pl.polsl.Controller;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

/**
 * JavaFX App main class.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
public class App extends Application {

    /**
     * Scene for JavaFX App.
     */
    private static Scene scene;

    /**
     * Create new scene for JavaFX Application.
     *
     * @param stage .
     * @throws IOException if there is invalid fxml file.
     */
    @Override
    public void start(Stage stage) throws IOException {
        scene = new Scene(loadFXML("window"), 600, 400);
        stage.setScene(scene);
        stage.setResizable(false);
        stage.setTitle("Sort Visualization 1.0");
        stage.show();
    }

    /**
     * Set Root for the scene.
     *
     * @param fxml fxml file with UI.
     * @throws IOException if there is invalid fxml file.
     */
    static void setRoot(String fxml) throws IOException {
        scene.setRoot(loadFXML(fxml));
    }

    /**
     * Load fxml file.
     *
     * @param fxml name of fxml file.
     * @return .
     * @throws IOException if there is invalid fxml file.
     */
    private static Parent loadFXML(String fxml) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(App.class.getResource(fxml + ".fxml"));
        return fxmlLoader.load();
    }

    /**
     * Main method which launch Application.
     *
     * @param args .
     */
    public static void main(String[] args) {
        launch();
    }

}
