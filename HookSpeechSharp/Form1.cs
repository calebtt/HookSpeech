using System.Text;

namespace HookSpeechSharp
{
    public partial class HssMainForm : Form
    {
        private const int NumElements = 52;
        private const string MsgTogglehooksDisable = "Disable";
        private const string MsgTogglehooksEnable = "Enable";
        private const string MsgBadTranslation = "Can't update translation alphabet, most likely bad string length.";
        private const string MsgBadError = "Error";
        public HssMainForm()
        {
            InitializeComponent();
            HookProcDllWrapper.AddHooks();
            UpdateTranslationBox();
            InitTextBoxes();
        }

        private string BuildStringFromTextBoxes()
        {
            StringBuilder sb = new();
            for (int i = NumElements; i < NumElements*2; i++)
                sb.Append(flowLayoutPanel1.Controls[i].Text);
            return sb.ToString();
        }

        private void InitTextBoxes()
        {
            string working = HookProcDllWrapper.GetWorkingAlphabet();
            string translation = HookProcDllWrapper.GetTranslationAlphabet();
            const int width = 16;
            const int height = 18;
            const float fontSize = 8.5f;
            //local func
            void TextBoxLoop(int count, bool isReadOnly, string textContent)
            {
                if (count != textContent.Length)
                    throw new ArgumentException("Dissimilar size in InitTextBoxes()::TextBoxLoop()");
                for (int i = 0; i < count; i++)
                {
                    TextBox tb1 = new();
                    Font f = new(FontFamily.GenericMonospace, fontSize);
                    tb1.MaxLength = 1;
                    tb1.Text = textContent.ElementAt(i).ToString();
                    tb1.Font = f;
                    tb1.Multiline = false;
                    tb1.BackColor = Color.MediumSpringGreen;
                    tb1.Margin = new(0, 0, 0, 0);
                    tb1.ReadOnly = isReadOnly;
                    tb1.MaximumSize = new(width, height);
                    tb1.MinimumSize = new(width, height);
                    //tb1.Padding = new(10, 10, 10, 10);
                    tb1.BorderStyle = BorderStyle.FixedSingle;
                    tb1.TextAlign = HorizontalAlignment.Center;
                    tb1.Visible = true;
                    this.flowLayoutPanel1.Controls.Add(tb1);
                }
            }
            TextBoxLoop(NumElements, true, working);
            TextBoxLoop(NumElements, false, translation);
        }

        private void UpdateTextBoxes()
        {
            string current = HookProcDllWrapper.GetWorkingAlphabet() + HookProcDllWrapper.GetTranslationAlphabet();
            for (int i = 0; i < NumElements*2; i++)
            {
                string charValue = current.ElementAt(i).ToString();
                this.flowLayoutPanel1.Controls[i].Text = charValue;
            }
        }

        private void UpdateTranslationBox()
        {
            tbxAlphabetChars.Text = HookProcDllWrapper.GetTranslationAlphabet();
        }

        private void UpdateToggleHooksButton()
        {
            this.btnToggleEnabled.Text = HookProcDllWrapper.IsHooked() ? MsgTogglehooksDisable : MsgTogglehooksEnable;
        }

        private void btnToggleEnabled_Click(object sender, EventArgs e)
        {
            if (HookProcDllWrapper.IsHooked())
            {
                HookProcDllWrapper.RemoveHooks();
            }
            else
            {
                HookProcDllWrapper.AddHooks();
            }
            UpdateToggleHooksButton();
        }

        private void btnUpdateAlphabet_Click(object sender, EventArgs e)
        {
            //build string from textbox text values
            string newAlphabet = BuildStringFromTextBoxes();
            //compare to existing internal translationalphabet
            bool isSameLength = newAlphabet.Length == HookProcDllWrapper.GetTranslationAlphabet().Length;
            bool isModified = !newAlphabet.Equals(HookProcDllWrapper.GetTranslationAlphabet());
            if (isSameLength && isModified)
            {
                //set translation alphabet to new values
                HookProcDllWrapper.SetTranslationAlphabet(newAlphabet);
            }
            else if (!HookProcDllWrapper.SetTranslationAlphabet(tbxAlphabetChars.Text))
            {
                MessageBox.Show(MsgBadTranslation, MsgBadError, MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
            }
            UpdateTranslationBox();
            UpdateTextBoxes();
        }

        private void HssMainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            HookProcDllWrapper.RemoveHooks();
        }
    }
}