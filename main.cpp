// �E�B���h�E�֘A�̏���
#include "Window.h"

// �W�����C�u����
#include <cmath>
#include <memory>

// ����
const GgSimpleShader::Light light =
{
  { 0.2f, 0.2f, 0.2f, 1.0f },
  { 1.0f, 1.0f, 1.0f, 1.0f },
  { 1.0f, 1.0f, 1.0f, 1.0f },
  { 2.0f, 9.0f, 3.0f, 1.0f }
};

// �I�u�W�F�N�g�̍ގ�
const GgSimpleShader::Material material =
{
  { 0.7f, 0.5f, 0.5f, 1.0f },
  { 0.7f, 0.5f, 0.5f, 1.0f },
  { 0.2f, 0.2f, 0.2f, 1.0f },
  50.0f
};

// ���ʂ̍ގ�
const GgSimpleShader::Material tile =
{
  { 0.8f, 0.8f, 0.8f, 0.4f },
  { 0.8f, 0.8f, 0.8f, 0.4f },
  { 0.2f, 0.2f, 0.2f, 0.4f },
  30.0f
};

//
// ���C���v���O����
//
int main(int argc, const char *argv[])
{
  // �E�B���h�E���쐬����
  Window window("ggsample12");

  // �w�i�F���w�肷��
  glClearColor(0.1f, 0.2f, 0.3f, 0.0f);

  // �B�ʏ�����L���ɂ���
  glEnable(GL_DEPTH_TEST);
  glDisable(GL_CULL_FACE);
  glDepthFunc(GL_LEQUAL);

  // �A���t�@�u�����f�B���O�̐ݒ�
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // �����p�̃v���O�����I�u�W�F�N�g
  GgSimpleShader shader("simple.vert", "simple.frag");

  // �����p�̃v���O�����I�u�W�F�N�g
  GgSimpleShader mirror("mirror.vert", "simple.frag");

  // OBJ �t�@�C���̓ǂݍ���
  const std::unique_ptr<const GgElements> object(ggElementsObj("bunny.obj"));

  // ����
  const std::unique_ptr<const GgTriangles> rectangle(ggRectangle(4.0f, 4.0f));

  // �r���[�ϊ��s��� mv �ɋ��߂�
  const GgMatrix mv(ggLookat(0.0f, 2.0f, 4.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f));

  // �}�`�̃��f���ϊ��s��� mm �ɋ��߂�
  const GgMatrix mm(ggTranslate(0.0f, 0.7f, 0.0f));

  // �}�`�̋����ϊ��s��� mr �ɋ��߂�
  const GgMatrix mr(ggScale(1.0f, -1.0f, 1.0f));

  // �����̃��[���h���W�n�ɂ���������ʒu
  GLfloat normalpos[4];
  mv.projection(normalpos, light.position);
  
  // �����̃��[���h���W�n�ɂ���������ʒu
  GLfloat reflected[4];
  mr.projection(reflected, normalpos);

  // �E�B���h�E���J���Ă���Ԃ���Ԃ��`�悷��
  while (window.shouldClose() == GL_FALSE)
  {
    // ��ʏ���
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ���e�ϊ��s��
    const GgMatrix mp(ggPerspective(0.5f, window.getAspect(), 1.0f, 15.0f));

    // �����p�̃V�F�[�_�̑I��
    mirror.use();
    mirror.loadLightMaterial(light);
    mirror.loadLightPosition(reflected);

    // �����̕`��
    mirror.loadMaterial(material);
    mirror.loadMatrix(mp, mv * mm * window.getLeftTrackball());
    object->draw();

    // �����p�̃V�F�[�_�̑I��
    shader.use();
    mirror.loadLightMaterial(light);
    mirror.loadLightPosition(normalpos);

    // ���ʂ̕`��
    shader.loadMaterial(tile);
    shader.loadMatrix(mp, mv.rotateX(-1.5707963f));
    glEnable(GL_BLEND);
    rectangle->draw();
    glDisable(GL_BLEND);

    // �����̕`��
    shader.loadMaterial(material);
    shader.loadMatrix(mp, mv * mm * window.getLeftTrackball());
    object->draw();

    // �J���[�o�b�t�@�����ւ��ăC�x���g�����o��
    window.swapBuffers();
  }

  return 0;
}
