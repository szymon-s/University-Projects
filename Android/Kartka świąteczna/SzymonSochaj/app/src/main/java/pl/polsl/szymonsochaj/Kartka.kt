package pl.polsl.szymonsochaj

import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.webkit.JavascriptInterface
import android.webkit.WebView
import android.widget.Toast

class Kartka : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        //WebView - kontrolka wyswietlajaca html
        val page = WebView(this)

        //wlaczenie obslugi JS
        page.settings.javaScriptEnabled = true

        //dodanie interfejsu pomiędzy Kotlinem a JS
        //this - obiekt tej klasy dostarcza metody JSInterface, activity - nazwa widoczna w JS
        page.addJavascriptInterface(this, "activity")

        //zaladowanie zawartosci kontroli WebView - pliki z katalogu assests w projekcie
        page.loadUrl("file:///android_asset/kartka.html")

        //wstawienie kontrolki WebView jako calej fasady aktywnosci
        setContentView(page)
    }


    fun zrobListePrezentow(): String {
        var listaPrezentow: String = String()
        for (element in getIntent().getStringArrayListExtra("prezenty")) {
            listaPrezentow += "- $element</br>"
        }
        return listaPrezentow
    }

    fun przygotujObraz(): String {

        return "url('" + intent.getStringExtra("zdjecie") + "')"
    }

    @JavascriptInterface
    fun wyswietlLokalizacje(): String {
        return "φ: " + intent.getStringExtra("szerokosc") + "<br>λ: " + intent.getStringExtra("dlugosc")
    }

    @JavascriptInterface
    fun wyswietlPrezenty(): String {
        return zrobListePrezentow()
    }

    @JavascriptInterface
    fun wyswietlZdjecie(): String {
        return przygotujObraz()
    }
}

