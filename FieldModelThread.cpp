#include "FieldModelThread.h"

QMutex *FieldModelThread::mutexField = 0;

FieldModelThread::FieldModelThread(QObject *parent) :
	QThread(parent), _canceled(false),
	_field(0), _animationId(0),
	_animate(true)
{
	if(mutexField == 0) {
		mutexField = new QMutex();
	}
}

FieldModelThread::~FieldModelThread()
{
	cancel();
	wait();
}

void FieldModelThread::setField(Field *field)
{
	mutexField->lock();
	_field = field;
	mutexField->unlock();
}

void FieldModelThread::setModel(int modelId, int animationId, bool animate)
{
	mutex.lock();
	_modelIds.clear();
	_modelIds.append(modelId);
	_animationId = animationId;
	_animate = animate;
	mutex.unlock();
}

void FieldModelThread::setModels(const QList<int> &modelIds, bool animate)
{
	mutex.lock();
	_modelIds = modelIds;
	_animationId = 0;
	_animate = animate;
	mutex.unlock();
}

void FieldModelThread::cancel()
{
	mutex.lock();
	_canceled = true;
	mutex.unlock();
}

void FieldModelThread::run()
{
	if(!_field) {
		qWarning() << "FieldModelThread::run() -> No field provided!";
		return;
	}

	mutex.lock();
	_canceled = false;
	QList<int> modelIds = _modelIds;
	int animationId = _animationId;
	bool animate = _animate;
	mutex.unlock();

	mutexField->lock();
	Field *field = _field;
	foreach(int modelId, modelIds) {
		if(_canceled) {
			mutexField->unlock();
			return;
		}
		FieldModelFile *fieldModel = field->fieldModel(modelId, animationId, animate);
		if(!_canceled && fieldModel->isOpen()) {
			emit modelLoaded(field, fieldModel, modelId, animationId, animate);
		}
	}
	mutexField->unlock();
}