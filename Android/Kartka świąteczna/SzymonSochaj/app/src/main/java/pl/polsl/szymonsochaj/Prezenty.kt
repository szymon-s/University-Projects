package pl.polsl.szymonsochaj

import android.Manifest
import android.annotation.SuppressLint
import android.app.Activity

import android.content.Intent
import android.content.pm.PackageManager
import android.location.Location
import android.location.LocationManager
import android.net.Uri
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.os.Environment
import android.os.StrictMode
import android.provider.MediaStore
import android.speech.RecognizerIntent
import android.webkit.JavascriptInterface
import android.webkit.WebView
import android.widget.Toast
import androidx.core.app.ActivityCompat
import java.io.File
import java.util.*

class Prezenty : AppCompatActivity() {

    var prezenty: ArrayList<String?>? = ArrayList<String?>()
    var prezentPobrany: Boolean = false
    var zdjecieZrobione: Boolean = false
    var dlugosc: String = String()
    var szerokosc: String = String()
    lateinit var plik: File

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        plik = File((applicationContext.getExternalFilesDir(Environment.DIRECTORY_PICTURES)?.path) + "/zdjecieKartka.jpg")

        var builder: StrictMode.VmPolicy.Builder = StrictMode.VmPolicy.Builder()
        StrictMode.setVmPolicy(builder.build())

        //WebView - kontrolka wyswietlajaca html
        val page = WebView(this)

        //wlaczenie obslugi JS
        page.settings.javaScriptEnabled = true

        //dodanie interfejsu pomiędzy Kotlinem a JS
        //this - obiekt tej klasy dostarcza metody JSInterface, activity - nazwa widoczna w JS
        page.addJavascriptInterface(this, "activity")

        //zaladowanie zawartosci kontroli WebView - pliki z katalogu assests w projekcie
        page.loadUrl("file:///android_asset/prezenty.html")

        //wstawienie kontrolki WebView jako calej fasady aktywnosci
        setContentView(page)
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)

        if (requestCode == 0) {
            if (resultCode == RESULT_OK) {
                if(!data?.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS)?.get(0)?.contains(".*iPhon.*".toRegex())!!) {
                    prezenty?.add(data?.getStringArrayListExtra(RecognizerIntent.EXTRA_RESULTS)?.get(0))

                }
                else{
                    prezenty?.add("CHCE TELEFON Z ANDROIDEM!")
                }
                prezentPobrany = true
            } else {
                prezentPobrany = true
            }

        } else if (requestCode == 1) {
            zdjecieZrobione = true

        }
    }

    fun wspolrzedna(pomiar: Double?): IntArray {
        var w: IntArray = IntArray(3)
        w[0] = pomiar?.toInt()!!
        w[1] = ((pomiar - w[0]) * 100).toInt()
        w[2] = ((pomiar - w[0] - w[1] * 0.01) * 10000).toInt()
        w[1] = (w[1] * 0.6).toInt()
        w[2] = (w[2] * 0.6).toInt()
        return w
    }


    fun aktualizuj(pomiar: Location?) {
        var lambda: IntArray = wspolrzedna(pomiar?.longitude)
        var fi: IntArray = wspolrzedna(pomiar?.latitude)
        dlugosc = lambda[0].toString() + "° " + lambda[1].toString() + "' " + lambda[2].toString() + "\""
        szerokosc = fi[0].toString() + "° " + fi[1].toString() + "' " + fi[2].toString() + "\""
    }

    @JavascriptInterface
    fun zrobListePrezentow(): String {
        var listaPrezentow: String = String()
        for (element in this.prezenty!!) {
            listaPrezentow += "- $element</br>"
        }
        prezentPobrany = false
        return listaPrezentow
    }

    @JavascriptInterface
    fun pobierzLokalizacje() {
        var gps: LocationManager = getSystemService(LOCATION_SERVICE) as LocationManager
        var uprawnienia: Array<String> = Array<String>(1) { Manifest.permission.ACCESS_FINE_LOCATION }
        ActivityCompat.requestPermissions(this, uprawnienia, 0)
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.ACCESS_FINE_LOCATION) != PackageManager.PERMISSION_GRANTED) {
            return
        }
        aktualizuj(gps.getLastKnownLocation(LocationManager.NETWORK_PROVIDER))
    }


    @JavascriptInterface
    fun czyZdjecieZrobione(): Boolean {
        return zdjecieZrobione
    }

    @JavascriptInterface
    fun czyPrezentPobrany(): Boolean {
        return prezentPobrany
    }

    @JavascriptInterface
    fun zrobZdjecie() {
        plik.delete()
        plik = File((applicationContext.getExternalFilesDir(Environment.DIRECTORY_PICTURES)?.path) + "/zdjecieKartka.jpg")
        var sciezkaDoPliku: Uri = Uri.fromFile(plik)
        var przejscie: Intent = Intent(MediaStore.ACTION_IMAGE_CAPTURE)
        przejscie.putExtra(MediaStore.EXTRA_OUTPUT, sciezkaDoPliku)
        startActivityForResult(przejscie, 1)
    }


    @JavascriptInterface //adnotacja sygnalizujaca ze metoda bedzie dostepna z poziomu JS
    fun pobierzPrezent() {
        val wywolanie: Intent = Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH)
        wywolanie.putExtra(RecognizerIntent.EXTRA_LANGUAGE_MODEL, RecognizerIntent.LANGUAGE_MODEL_FREE_FORM)
        startActivityForResult(wywolanie, 0)
    }


    @JavascriptInterface
    fun zrobKartke() {
        var intent: Intent = Intent(this, Kartka::class.java)
        intent.putExtra("prezenty", prezenty)
        intent.putExtra("zdjecie", Uri.fromFile(plik).toString())
        intent.putExtra("szerokosc", szerokosc)
        intent.putExtra("dlugosc", dlugosc)
        startActivity(intent)
        zdjecieZrobione = false
    }

    @JavascriptInterface
    fun inicjalizacja(): String {
        prezenty?.clear()
        szerokosc = String()
        dlugosc = String()
        return zrobListePrezentow()
    }
}