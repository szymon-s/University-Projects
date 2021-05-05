package pl.polsl.servlets;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.Part;
import pl.polsl.Model.Model;

/**
 * Servlet which handle choosing the file and saving it on the server and
 * sending result to the client.
 *
 * @author Szymon Sochaj
 * @version 1.0
 */
@WebServlet(name = "FileChooser", urlPatterns = {"/FileChooser"})
public class FileChooserServlet extends HttpServlet {

    /**
     * Model which stores data for sort visualization and implements sort
     * algorithms.
     */
    private Model model = new Model();

    /**
     * Set file to the model.
     *
     * @param file with data to be sorted.
     */
    private void setModelsFile(File file) {
        this.model.setFile(file);
    }

    /**
     * Handles the HTTP <code>POST</code> method which loads file send by user,
     * saves it on the server and sets it to the model, also it provides
     * response to the client with information about result of loading the file.
     *
     * @param request servlet request
     * @param response servlet response
     * @throws ServletException if a servlet-specific error occurs
     * @throws IOException if an I/O error occurs
     */
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        model = (Model) request.getSession().getAttribute("model"); //get model from session

        if (model == null) {                                        //if there is no model create it using CreateModelServlet
            getServletContext().getRequestDispatcher("/CreateModel").include(request, response);
            model = (Model) request.getSession().getAttribute("model");
        }

        String htmlCode = "<!DOCTYPE html>\n"
                + "<html>\n"
                + "    <head>\n"
                + "        <meta http-equiv=\"Content-Type\" content=\"text/html; charset=UTF-8\">\n"
                + "        <title>Sort Visualization</title>\n"
                + "    </head>\n"
                + "    <body style=\"text-align:center; padding: 10% 0;\">\n"
                + "        <div style=\" height:auto; border: 3px solid black; margin: auto; width: 50%;background-color: #a6faff;\"> ";

        response.setContentType("text/html; charset=UTF-8");
        PrintWriter out = response.getWriter();
        Part filePart = request.getPart("dataFile");

        if (filePart != null) {
            try {
                InputStream fileContent = filePart.getInputStream();
                File file = new File(filePart.getSubmittedFileName()); //create new file
                OutputStream outputFile = new FileOutputStream(file);

                while (true) {                                        //load data from loaded file to new file
                    int element = fileContent.read();
                    if (element > 0) {
                        outputFile.write(element);
                    } else {
                        break;
                    }
                }
                fileContent.close();
                outputFile.close();
                setModelsFile(file);
                htmlCode += "File loaded: " + file.getName();
            } catch (FileNotFoundException e) {
                setModelsFile(null);
                htmlCode += "No file loaded.";
            }
        } else {
            htmlCode += "Error during file loading.";
        }
        htmlCode += "</div>"
                + "<br/><br/>"
                + "<form action=\"index.html\">"
                + "<input type=\"submit\" value=\"Back\"/>"
                + "</form>"
                + "</body>"
                + "</html>";
        out.print(htmlCode);
    }
}
