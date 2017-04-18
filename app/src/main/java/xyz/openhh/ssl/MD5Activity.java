package xyz.openhh.ssl;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.RadioGroup;
import android.widget.ScrollView;
import android.widget.TextView;

public class MD5Activity extends AppCompatActivity implements View.OnClickListener {

    EditText calculateInput;
    TextView calculateResult;
    ScrollView scrollView;
    RadioGroup radioGroup;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_md5);


        findViewById(R.id.md5_calculate).setOnClickListener(this);
        findViewById(R.id.btn_clear).setOnClickListener(this);

        calculateInput = (EditText) findViewById(R.id.calculate_input);
        calculateResult = (TextView) findViewById(R.id.calculate_result);
        scrollView = (ScrollView) findViewById(R.id.scroll_view);
        radioGroup = (RadioGroup) findViewById(R.id.radioGroup);
//        calculateResult.setMovementMethod(ScrollingMovementMethod.getInstance());
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.md5_calculate:
                int checkId = radioGroup.getCheckedRadioButtonId();
                StringBuilder sBuilder = new StringBuilder("\r\n");
                if (checkId == R.id.rb_md5)
                    calculateResult.append(sBuilder.append(NativeSSL.getStrMd5(calculateInput.getText().toString())));
                else if (checkId == R.id.rb_aes) {
                    try {
                        byte[] oriData = calculateInput.getText().toString().getBytes("UTF-8");

                        byte[] result = NativeSSL.aesEncrypt(oriData);
                        calculateResult.append(sBuilder.append("C++加密，Java解密:").append(AES.decrypt(result)));

                        byte[] result2 = AES.encrypt(calculateInput.getText().toString());
                        sBuilder.delete(0, sBuilder.length());
                        calculateResult.append(sBuilder.append("\r\nJava加密，C++解密:").append(NativeSSL.aesDecrypt(result2)));
                    } catch (Exception e) {

                    }
                }
                scrollView.fullScroll(ScrollView.FOCUS_DOWN);
                break;
            case R.id.btn_clear:
                calculateResult.setText("结果：");
                break;
        }
    }
}
