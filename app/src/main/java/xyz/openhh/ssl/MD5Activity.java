package xyz.openhh.ssl;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class MD5Activity extends AppCompatActivity implements View.OnClickListener {

    EditText calculateInput;
    TextView calculateResult;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_md5);


        findViewById(R.id.md5_calculate).setOnClickListener(this);
        findViewById(R.id.btn_clear).setOnClickListener(this);

        calculateInput = (EditText) findViewById(R.id.calculate_input);
        calculateResult = (TextView) findViewById(R.id.calculate_result);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.md5_calculate:
                calculateResult.append(new StringBuilder("\r\n").append(NativeSSL.getStrMd5(calculateInput.getText().toString())));
                break;
            case R.id.btn_clear:
                break;
        }
    }
}
