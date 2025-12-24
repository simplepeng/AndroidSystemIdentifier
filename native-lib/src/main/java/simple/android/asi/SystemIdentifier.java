package simple.android.asi;

public class SystemIdentifier {

    static {
        System.loadLibrary("asi");
    }

    public native static String getUpdateMark();

    public native static String getBootMark();

}