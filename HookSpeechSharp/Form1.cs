namespace HookSpeechSharp
{
    public partial class HssMainForm : Form
    {
        private const int NumElements = 52;
        private const string MsgTogglehooksDisable = "Disable";
        private const string MsgTogglehooksEnable = "Enable";
        private const string MsgBadTranslation = "Can't update translation alphabet, most likely bad string length.";
        private const string MsgBadError = "Error";
        private readonly HookProcDllWrapper dllWrapper = new HookProcDllWrapper();
        public HssMainForm()
        {
            InitializeComponent();
            dllWrapper.AddHooks();
            UpdateTranslationBox();
            BuildTextBoxes();
        }
        private void BuildTextBoxes()
        {
            string working = dllWrapper.GetWorkingAlphabet();
            string translation = dllWrapper.GetTranslationAlphabet();
            const int width = 16;
            const int height = 18;
            const float fontSize = 8.5f;
            for (int i = 0; i < NumElements; i++)
            {
                TextBox tb1 = new();
                Font f = new(FontFamily.GenericMonospace, fontSize);
                tb1.Text = working.ElementAt(i).ToString();
                tb1.Font = f;
                tb1.Multiline = false;
                tb1.BackColor = Color.MediumSpringGreen;
                tb1.Margin = new(0, 0, 0, 0);
                tb1.ReadOnly = true;
                tb1.MaximumSize = new(width, height);
                tb1.MinimumSize = new(width, height);
                //tb1.Padding = new(10, 10, 10, 10);
                tb1.TextAlign = HorizontalAlignment.Center;
                tb1.Visible = true;
                this.flowLayoutPanel1.Controls.Add(tb1);
            }
            for (int i = 0; i < NumElements; i++)
            {
                TextBox tb1 = new();
                Font f = new(FontFamily.GenericMonospace, fontSize);
                tb1.Text = translation.ElementAt(i).ToString();
                tb1.Font = f;
                tb1.Multiline = false;
                tb1.BackColor = Color.MediumSpringGreen;
                tb1.Margin = new(0, 0, 0, 0);
                tb1.ReadOnly = true;
                tb1.MaximumSize = new(width, height);
                tb1.MinimumSize = new(width, height);
                //tb1.Padding = new(10, 10, 10, 10);
                tb1.TextAlign = HorizontalAlignment.Center;
                tb1.Visible = true;
                this.flowLayoutPanel1.Controls.Add(tb1);
            }
        }

        private void UpdateTextBoxes()
        {
            string current = dllWrapper.GetWorkingAlphabet() + dllWrapper.GetTranslationAlphabet();
            for (int i = 0; i < NumElements*2; i++)
            {
                string charValue = current.ElementAt(i).ToString();
                this.flowLayoutPanel1.Controls[i].Text = charValue;
            }
        }
        private void UpdateTranslationBox()
        {
            tbxAlphabetChars.Text = dllWrapper.GetTranslationAlphabet();
        }

        private void UpdateToggleHooksButton()
        {
            this.btnToggleEnabled.Text = dllWrapper.IsHooked() ? MsgTogglehooksDisable : MsgTogglehooksEnable;
        }

        private void btnToggleEnabled_Click(object sender, EventArgs e)
        {
            if (dllWrapper.IsHooked())
            {
                dllWrapper.RemoveHooks();
            }
            else
            {
                dllWrapper.AddHooks();
            }
            UpdateToggleHooksButton();
        }

        private void btnUpdateAlphabet_Click(object sender, EventArgs e)
        {
            if(!dllWrapper.SetTranslationAlphabet(tbxAlphabetChars.Text))
            {
                MessageBox.Show(MsgBadTranslation, MsgBadError, MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
            }
            UpdateTranslationBox();
            UpdateTextBoxes();
        }

        private void HssMainForm_FormClosing(object sender, FormClosingEventArgs e)
        {
            dllWrapper.RemoveHooks();
        }
    }
}