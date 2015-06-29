//package uku_control;
//
//import org.junit.Test;
//import uku_control.config.Configuration;
//import uku_control.config.Parameter;
//import uku_control.config.TableType;
//import uku_control.config.ViewConfiguration;
//
//import javax.swing.text.View;
//import javax.xml.bind.JAXBContext;
//import javax.xml.bind.Marshaller;
//import javax.xml.bind.Unmarshaller;
//
//import java.io.StringReader;
//import java.io.StringWriter;
//
//public class ParameterTest {
//
//    @Test
//    public void testsasdf() throws Exception {
//        int i = Integer.parseInt("01", 16);
//
//    }
//
//    @Test
//    public void testUti() throws Exception {
//        Configuration configuration = Util.loadConfiguration();
//        System.out.println(configuration);
//
//    }
//
//    @Test
//    public void testName() throws Exception {
//        Parameter<String> stringParameter = new Parameter<String>();
//        stringParameter.setName("������� �������");
//        stringParameter.setOid("1.1.1.2..23.3.");
//        stringParameter.setType(Type.OCTET_STRING);
//        Configuration configuration = new Configuration();
////        configuration.getParameters().add(stringParameter);
////        configuration.getParameters().add(stringParameter);
//
//        ViewConfiguration viewConfiguration = new ViewConfiguration();
//        viewConfiguration.getParameters().add(stringParameter);
//        viewConfiguration.setTableCaption("��������");
//        viewConfiguration.setTableType(TableType.TWO_COLUMNS);
//        configuration.getViewConfigurations().add(viewConfiguration);
//
//        JAXBContext jc = JAXBContext.newInstance(Configuration.class, ViewConfiguration.class,
//                Parameter.class);
//
//        // Marshal
//        Marshaller marshaller = jc.createMarshaller();
//        marshaller.setProperty(Marshaller.JAXB_FORMATTED_OUTPUT, true);
//        StringWriter writer = new StringWriter();
//        marshaller.marshal(configuration, writer);
//        String output = writer.toString();
//        System.out.println(output);
//        Unmarshaller unmarshaller = jc.createUnmarshaller();
//        Object unmarshal = unmarshaller.unmarshal(new StringReader(output));
//        System.out.println(unmarshal);
//
//
//    }
//}