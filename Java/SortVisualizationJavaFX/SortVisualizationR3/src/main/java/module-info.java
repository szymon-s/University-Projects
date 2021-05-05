module pl.polsl.Controller {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.base;

    opens pl.polsl.Controller to javafx.fxml;
    exports pl.polsl.Controller;
}
